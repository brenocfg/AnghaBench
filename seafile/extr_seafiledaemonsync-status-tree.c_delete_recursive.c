#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t guint ;
struct TYPE_8__ {int /*<<< orphan*/  dirents; } ;
struct TYPE_7__ {TYPE_2__* subdir; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ SyncStatusDirent ;
typedef  TYPE_2__ SyncStatusDir ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 TYPE_1__* g_hash_table_lookup (int /*<<< orphan*/ ,char*) ; 
 char* g_strconcat (char const*,char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ is_empty_dir (TYPE_1__*) ; 
 int /*<<< orphan*/  remove_item (TYPE_2__*,char*,char*) ; 

__attribute__((used)) static void
delete_recursive (SyncStatusDir *dir, char **dnames, guint n, guint i,
                  const char *base)
{
    char *dname;
    SyncStatusDirent *dirent;
    char *fullpath = NULL;

    dname = dnames[i];
    fullpath = g_strconcat (base, "/", dname, NULL);

    dirent = g_hash_table_lookup (dir->dirents, dname);
    if (dirent) {
        if (S_ISDIR(dirent->mode)) {
            if (i == (n-1)) {
                if (is_empty_dir(dirent))
                    remove_item (dir, dname, fullpath);
            } else {
                delete_recursive (dirent->subdir, dnames, n, ++i, fullpath);
                /* If this dir becomes empty after deleting the entry below,
                 * remove the dir itself too.
                 */
                if (is_empty_dir(dirent))
                    remove_item (dir, dname, fullpath);
            }
        } else if (i == (n-1)) {
            remove_item (dir, dname, fullpath);
        }
    }

    g_free (fullpath);
}