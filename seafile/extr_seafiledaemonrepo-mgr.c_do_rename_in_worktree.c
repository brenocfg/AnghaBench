#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  new_name; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  GHashTable ;
typedef  TYPE_1__ DiffEntry ;

/* Variables and functions */
 char* build_checkout_path (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 char* g_build_filename (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ seaf_util_exists (char*) ; 
 scalar_t__ seaf_util_rename (char*,char*) ; 
 int /*<<< orphan*/  seaf_warning (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
do_rename_in_worktree (DiffEntry *de, const char *worktree,
                       GHashTable *conflict_hash, GHashTable *no_conflict_hash)
{
    char *old_path, *new_path;
    int ret = 0;

    old_path = g_build_filename (worktree, de->name, NULL);

    if (seaf_util_exists (old_path)) {
        new_path = build_checkout_path (worktree, de->new_name, strlen(de->new_name));
        if (!new_path) {
            ret = -1;
            goto out;
        }

        if (seaf_util_rename (old_path, new_path) < 0) {
            seaf_warning ("Failed to rename %s to %s: %s.\n",
                          old_path, new_path, strerror(errno));
            ret = -1;
        }

        g_free (new_path);
    }

out:
    g_free (old_path);
    return ret;
}