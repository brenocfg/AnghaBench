#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  ChangeSetDirent ;
typedef  int /*<<< orphan*/  ChangeSet ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  changeset_dirent_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * delete_from_tree (int /*<<< orphan*/ *,char const*,scalar_t__*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup (char const*) ; 
 scalar_t__ strlen (char const*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static void
remove_from_changeset_recursive (ChangeSet *changeset,
                                 const char *path,
                                 gboolean remove_parent,
                                 const char *top_dir)
{
    ChangeSetDirent *dent;
    gboolean parent_empty = FALSE;

    dent = delete_from_tree (changeset, path, &parent_empty);
    changeset_dirent_free (dent);

    if (remove_parent && parent_empty) {
        char *parent = g_strdup(path);
        char *slash = strrchr (parent, '/');
        if (slash) {
            *slash = '\0';
            if (strlen(parent) >= strlen(top_dir)) {
                /* Recursively remove parent dirs. */
                remove_from_changeset_recursive (changeset,
                                                 parent,
                                                 remove_parent,
                                                 top_dir);
            }
        }
        g_free (parent);
    }
}