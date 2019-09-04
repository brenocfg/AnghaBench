#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  (* TraverseFSPathCallback ) (int /*<<< orphan*/ *,char*,TYPE_1__*,void*,scalar_t__*) ;
struct TYPE_11__ {scalar_t__ data; struct TYPE_11__* next; } ;
struct TYPE_10__ {TYPE_4__* entries; } ;
struct TYPE_9__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  SeafFSManager ;
typedef  TYPE_1__ SeafDirent ;
typedef  TYPE_3__ SeafDir ;
typedef  TYPE_4__ GList ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strconcat (char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_dir_free (TYPE_3__*) ; 
 TYPE_3__* seaf_fs_manager_get_seafdir (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
traverse_dir_path (SeafFSManager *mgr,
                   const char *repo_id,
                   int version,
                   const char *dir_path,
                   SeafDirent *dent,
                   TraverseFSPathCallback callback,
                   void *user_data)
{
    SeafDir *dir;
    GList *p;
    SeafDirent *seaf_dent;
    gboolean stop = FALSE;
    char *sub_path;
    int ret = 0;

    if (!callback (mgr, dir_path, dent, user_data, &stop))
        return -1;

    if (stop)
        return 0;

    dir = seaf_fs_manager_get_seafdir (mgr, repo_id, version, dent->id);
    if (!dir) {
        seaf_warning ("get seafdir %s:%s failed\n", repo_id, dent->id);
        return -1;
    }

    for (p = dir->entries; p; p = p->next) {
        seaf_dent = (SeafDirent *)p->data;
        sub_path = g_strconcat (dir_path, "/", seaf_dent->name, NULL);

        if (S_ISREG(seaf_dent->mode)) {
            if (!callback (mgr, sub_path, seaf_dent, user_data, &stop)) {
                g_free (sub_path);
                ret = -1;
                break;
            }
        } else if (S_ISDIR(seaf_dent->mode)) {
            if (traverse_dir_path (mgr, repo_id, version, sub_path, seaf_dent,
                                   callback, user_data) < 0) {
                g_free (sub_path);
                ret = -1;
                break;
            }
        }
        g_free (sub_path);
    }

    seaf_dir_free (dir);
    return ret;
}