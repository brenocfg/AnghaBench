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
typedef  int /*<<< orphan*/  GKeyFile ;
typedef  int /*<<< orphan*/  BlockBackend ;

/* Variables and functions */
 int /*<<< orphan*/ * block_backend_fs_new (char*,char*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_key_file_get_string (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 

BlockBackend*
load_filesystem_block_backend(GKeyFile *config)
{
    BlockBackend *bend;
    char *tmp_dir;
    char *block_dir;
    
    block_dir = g_key_file_get_string (config, "block_backend", "block_dir", NULL);
    if (!block_dir) {
        seaf_warning ("Block dir not set in config.\n");
        return NULL;
    }

    tmp_dir = g_key_file_get_string (config, "block_backend", "tmp_dir", NULL);
    if (!tmp_dir) {
        seaf_warning ("Block tmp dir not set in config.\n");
        return NULL;
    }

    bend = block_backend_fs_new (block_dir, tmp_dir);

    g_free (block_dir);
    g_free (tmp_dir);
    return bend;
}