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
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_key_file_get_string (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * load_filesystem_block_backend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

BlockBackend*
load_block_backend (GKeyFile *config)
{
    char *backend;
    BlockBackend *bend;

    backend = g_key_file_get_string (config, "block_backend", "name", NULL);
    if (!backend) {
        return NULL;
    }

    if (strcmp(backend, "filesystem") == 0) {
        bend = load_filesystem_block_backend(config);
        g_free (backend);
        return bend;
    }

    seaf_warning ("Unknown backend\n");
    return NULL;
}