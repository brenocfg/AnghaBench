#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  obj_id ;
struct TYPE_5__ {int /*<<< orphan*/  obj_dir; int /*<<< orphan*/  v0_obj_dir; } ;
struct TYPE_4__ {TYPE_2__* priv; } ;
typedef  int /*<<< orphan*/  (* SeafObjFunc ) (char const*,int,char*,void*) ;
typedef  TYPE_1__ ObjBackend ;
typedef  int /*<<< orphan*/  GDir ;
typedef  TYPE_2__ FsPriv ;

/* Variables and functions */
 int SEAF_PATH_MAX ; 
 char* g_build_filename (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_dir_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_dir_open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* g_dir_read_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  seaf_warning (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
obj_backend_fs_foreach_obj (ObjBackend *bend,
                            const char *repo_id,
                            int version,
                            SeafObjFunc process,
                            void *user_data)
{
    FsPriv *priv = bend->priv;
    char *obj_dir = NULL;
    int dir_len;
    GDir *dir1 = NULL, *dir2;
    const char *dname1, *dname2;
    char obj_id[128];
    char path[SEAF_PATH_MAX], *pos;
    int ret = 0;

#if defined MIGRATION || defined SEAFILE_CLIENT
    if (version > 0)
        obj_dir = g_build_filename (priv->obj_dir, repo_id, NULL);
    else
        obj_dir = g_strdup(priv->v0_obj_dir);
#else
    obj_dir = g_build_filename (priv->obj_dir, repo_id, NULL);
#endif
    dir_len = strlen (obj_dir);

    dir1 = g_dir_open (obj_dir, 0, NULL);
    if (!dir1) {
        goto out;
    }

    memcpy (path, obj_dir, dir_len);
    pos = path + dir_len;

    while ((dname1 = g_dir_read_name(dir1)) != NULL) {
        snprintf (pos, sizeof(path) - dir_len, "/%s", dname1);

        dir2 = g_dir_open (path, 0, NULL);
        if (!dir2) {
            seaf_warning ("Failed to open object dir %s.\n", path);
            continue;
        }

        while ((dname2 = g_dir_read_name(dir2)) != NULL) {
            snprintf (obj_id, sizeof(obj_id), "%s%s", dname1, dname2);
            if (!process (repo_id, version, obj_id, user_data)) {
                g_dir_close (dir2);
                goto out;
            }
        }
        g_dir_close (dir2);
    }

out:
    if (dir1)
        g_dir_close (dir1);
    g_free (obj_dir);

    return ret;
}