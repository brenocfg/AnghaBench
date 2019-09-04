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
struct TYPE_5__ {TYPE_1__* be_priv; } ;
struct TYPE_4__ {char* block_dir; } ;
typedef  int /*<<< orphan*/  GDir ;
typedef  TYPE_1__ FsPriv ;
typedef  TYPE_2__ BlockBackend ;

/* Variables and functions */
 char* g_build_filename (char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_dir_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_dir_open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* g_dir_read_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_rmdir (char*) ; 
 int /*<<< orphan*/  g_unlink (char*) ; 
 int /*<<< orphan*/  seaf_warning (char*,char*) ; 

__attribute__((used)) static int
block_backend_fs_remove_store (BlockBackend *bend, const char *store_id)
{
    FsPriv *priv = bend->be_priv;
    char *block_dir = NULL;
    GDir *dir1, *dir2;
    const char *dname1, *dname2;
    char *path1, *path2;

    block_dir = g_build_filename (priv->block_dir, store_id, NULL);

    dir1 = g_dir_open (block_dir, 0, NULL);
    if (!dir1) {
        g_free (block_dir);
        return 0;
    }

    while ((dname1 = g_dir_read_name(dir1)) != NULL) {
        path1 = g_build_filename (block_dir, dname1, NULL);

        dir2 = g_dir_open (path1, 0, NULL);
        if (!dir2) {
            seaf_warning ("Failed to open block dir %s.\n", path1);
            g_dir_close (dir1);
            g_free (path1);
            g_free (block_dir);
            return -1;
        }

        while ((dname2 = g_dir_read_name(dir2)) != NULL) {
            path2 = g_build_filename (path1, dname2, NULL);
            g_unlink (path2);
            g_free (path2);
        }
        g_dir_close (dir2);

        g_rmdir (path1);
        g_free (path1);
    }

    g_dir_close (dir1);
    g_rmdir (block_dir);
    g_free (block_dir);

    return 0;
}