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
typedef  int /*<<< orphan*/  BlockBackend ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  F_OK ; 
 int SEAF_PATH_MAX ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ g_access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_block_path (int /*<<< orphan*/ *,char const*,char*,char const*,int) ; 

__attribute__((used)) static gboolean
block_backend_fs_block_exists (BlockBackend *bend,
                               const char *store_id,
                               int version,
                               const char *block_sha1)
{
    char block_path[SEAF_PATH_MAX];

    get_block_path (bend, block_sha1, block_path, store_id, version);
    if (g_access (block_path, F_OK) == 0)
        return TRUE;
    else
        return FALSE;
}