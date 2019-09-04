#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  (* TraverseFSTreeCallback ) (int /*<<< orphan*/ *,char const*,int,char const*,int /*<<< orphan*/ ,void*,scalar_t__*) ;
struct TYPE_8__ {scalar_t__ data; struct TYPE_8__* next; } ;
struct TYPE_7__ {TYPE_3__* entries; } ;
struct TYPE_6__ {char* id; int /*<<< orphan*/  mode; } ;
typedef  int /*<<< orphan*/  SeafFSManager ;
typedef  TYPE_1__ SeafDirent ;
typedef  TYPE_2__ SeafDir ;
typedef  TYPE_3__ GList ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SEAF_METADATA_TYPE_DIR ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_dir_free (TYPE_2__*) ; 
 TYPE_2__* seaf_fs_manager_get_seafdir (int /*<<< orphan*/ *,char const*,int,char const*) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*) ; 
 scalar_t__ traverse_file (int /*<<< orphan*/ *,char const*,int,char*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,char const*,int,char const*,int /*<<< orphan*/ ,void*,scalar_t__*),void*,scalar_t__) ; 

__attribute__((used)) static int
traverse_dir (SeafFSManager *mgr,
              const char *repo_id,
              int version,
              const char *id,
              TraverseFSTreeCallback callback,
              void *user_data,
              gboolean skip_errors)
{
    SeafDir *dir;
    GList *p;
    SeafDirent *seaf_dent;
    gboolean stop = FALSE;

    if (!callback (mgr, repo_id, version,
                   id, SEAF_METADATA_TYPE_DIR, user_data, &stop) &&
        !skip_errors)
        return -1;

    if (stop)
        return 0;

    dir = seaf_fs_manager_get_seafdir (mgr, repo_id, version, id);
    if (!dir) {
        seaf_warning ("[fs-mgr]get seafdir %s failed\n", id);
        if (skip_errors)
            return 0;
        return -1;
    }
    for (p = dir->entries; p; p = p->next) {
        seaf_dent = (SeafDirent *)p->data;

        if (S_ISREG(seaf_dent->mode)) {
            if (traverse_file (mgr, repo_id, version, seaf_dent->id,
                               callback, user_data, skip_errors) < 0) {
                if (!skip_errors) {
                    seaf_dir_free (dir);
                    return -1;
                }
            }
        } else if (S_ISDIR(seaf_dent->mode)) {
            if (traverse_dir (mgr, repo_id, version, seaf_dent->id,
                              callback, user_data, skip_errors) < 0) {
                if (!skip_errors) {
                    seaf_dir_free (dir);
                    return -1;
                }
            }
        }
    }

    seaf_dir_free (dir);
    return 0;
}