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
typedef  int guint64 ;
typedef  int gint64 ;
struct TYPE_8__ {scalar_t__ data; struct TYPE_8__* next; } ;
struct TYPE_7__ {scalar_t__ version; TYPE_3__* entries; } ;
struct TYPE_6__ {int size; char* id; int /*<<< orphan*/  mode; } ;
typedef  int /*<<< orphan*/  SeafFSManager ;
typedef  TYPE_1__ SeafDirent ;
typedef  TYPE_2__ SeafDir ;
typedef  TYPE_3__ GList ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_dir_free (TYPE_2__*) ; 
 int seaf_fs_manager_get_file_size (int /*<<< orphan*/ *,char const*,int,char*) ; 
 TYPE_2__* seaf_fs_manager_get_seafdir (int /*<<< orphan*/ *,char const*,int,char const*) ; 

__attribute__((used)) static gint64
get_dir_size (SeafFSManager *mgr, const char *repo_id, int version, const char *id)
{
    SeafDir *dir;
    SeafDirent *seaf_dent;
    guint64 size = 0;
    gint64 result;
    GList *p;

    dir = seaf_fs_manager_get_seafdir (mgr, repo_id, version, id);
    if (!dir)
        return -1;

    for (p = dir->entries; p; p = p->next) {
        seaf_dent = (SeafDirent *)p->data;

        if (S_ISREG(seaf_dent->mode)) {
            if (dir->version > 0)
                result = seaf_dent->size;
            else {
                result = seaf_fs_manager_get_file_size (mgr,
                                                        repo_id,
                                                        version,
                                                        seaf_dent->id);
                if (result < 0) {
                    seaf_dir_free (dir);
                    return result;
                }
            }
            size += result;
        } else if (S_ISDIR(seaf_dent->mode)) {
            result = get_dir_size (mgr, repo_id, version, seaf_dent->id);
            if (result < 0) {
                seaf_dir_free (dir);
                return result;
            }
            size += result;
        }
    }

    seaf_dir_free (dir);
    return size;
}