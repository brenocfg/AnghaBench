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
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  SeafStat ;
typedef  int /*<<< orphan*/  ChangeSetDirent ;
typedef  int /*<<< orphan*/  ChangeSet ;

/* Variables and functions */
#define  DIFF_STATUS_ADDED 131 
#define  DIFF_STATUS_DIR_ADDED 130 
#define  DIFF_STATUS_MODIFIED 129 
#define  DIFF_STATUS_RENAMED 128 
 int /*<<< orphan*/  add_to_tree (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  changeset_dirent_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * delete_from_tree (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
apply_to_tree (ChangeSet *changeset,
               char status,
               unsigned char *sha1,
               SeafStat *st,
               const char *modifier,
               const char *path,
               const char *new_path)
{
    ChangeSetDirent *dent, *dent_dst;
    gboolean dummy;

    switch (status) {
    case DIFF_STATUS_ADDED:
    case DIFF_STATUS_MODIFIED:
    case DIFF_STATUS_DIR_ADDED:
        add_to_tree (changeset, sha1, st, modifier, path, NULL);
        break;
    case DIFF_STATUS_RENAMED:
        dent = delete_from_tree (changeset, path, &dummy);
        if (!dent)
            break;

        dent_dst = delete_from_tree (changeset, new_path, &dummy);
        changeset_dirent_free (dent_dst);
        add_to_tree (changeset, NULL, NULL, NULL, new_path, dent);

        break;
    }
}