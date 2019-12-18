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
typedef  int /*<<< orphan*/  block_id ;
struct TYPE_5__ {TYPE_1__* be_priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  block_dir; int /*<<< orphan*/  v0_block_dir; } ;
typedef  int /*<<< orphan*/  (* SeafBlockFunc ) (char const*,int,char*,void*) ;
typedef  int /*<<< orphan*/  GDir ;
typedef  TYPE_1__ FsPriv ;
typedef  TYPE_2__ BlockBackend ;

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
block_backend_fs_foreach_block (BlockBackend *bend,
                                const char *store_id,
                                int version,
                                SeafBlockFunc process,
                                void *user_data)
{
    FsPriv *priv = bend->be_priv;
    char *block_dir = NULL;
    int dir_len;
    GDir *dir1 = NULL, *dir2;
    const char *dname1, *dname2;
    char block_id[128];
    char path[SEAF_PATH_MAX], *pos;
    int ret = 0;

#if defined MIGRATION
    if (version > 0)
        block_dir = g_build_filename (priv->block_dir, store_id, NULL);
    else
        block_dir = g_strdup(priv->v0_block_dir);
#else
    block_dir = g_build_filename (priv->block_dir, store_id, NULL);
#endif
    dir_len = strlen (block_dir);

    dir1 = g_dir_open (block_dir, 0, NULL);
    if (!dir1) {
        goto out;
    }

    memcpy (path, block_dir, dir_len);
    pos = path + dir_len;

    while ((dname1 = g_dir_read_name(dir1)) != NULL) {
        snprintf (pos, sizeof(path) - dir_len, "/%s", dname1);

        dir2 = g_dir_open (path, 0, NULL);
        if (!dir2) {
            seaf_warning ("Failed to open block dir %s.\n", path);
            continue;
        }

        while ((dname2 = g_dir_read_name(dir2)) != NULL) {
            snprintf (block_id, sizeof(block_id), "%s%s", dname1, dname2);
            if (!process (store_id, version, block_id, user_data)) {
                g_dir_close (dir2);
                goto out;
            }
        }
        g_dir_close (dir2);
    }

out:
    if (dir1)
        g_dir_close (dir1);
    g_free (block_dir);

    return ret;
}