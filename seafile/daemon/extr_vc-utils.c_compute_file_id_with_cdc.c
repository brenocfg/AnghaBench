#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  cdc ;
struct TYPE_5__ {scalar_t__ blk_sha1s; int /*<<< orphan*/  file_sum; int /*<<< orphan*/  write_block; void* block_max_sz; void* block_min_sz; void* block_sz; } ;
typedef  int /*<<< orphan*/  SeafileCrypt ;
typedef  int /*<<< orphan*/  SeafStat ;
typedef  TYPE_1__ CDCFileDescriptor ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ filename_chunk_cdc (char const*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  seaf_fs_manager_calculate_seafile_id_json (int,TYPE_1__*,unsigned char*) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 
 int /*<<< orphan*/  seafile_write_chunk ; 

__attribute__((used)) static int
compute_file_id_with_cdc (const char *path, SeafStat *st,
                          SeafileCrypt *crypt, int repo_version,
                          uint32_t blk_avg_size, uint32_t blk_min_size, uint32_t blk_max_size,
                          unsigned char sha1[])
{
    CDCFileDescriptor cdc;

    memset (&cdc, 0, sizeof(cdc));
    cdc.block_sz = blk_avg_size;
    cdc.block_min_sz = blk_min_size;
    cdc.block_max_sz = blk_max_size;
    cdc.write_block = seafile_write_chunk;
    if (filename_chunk_cdc (path, &cdc, crypt, FALSE) < 0) {
        seaf_warning ("Failed to chunk file.\n");
        return -1;
    }

    if (repo_version > 0)
        seaf_fs_manager_calculate_seafile_id_json (repo_version, &cdc, sha1);
    else
        memcpy (sha1, cdc.file_sum, 20);

    if (cdc.blk_sha1s)
        free (cdc.blk_sha1s);

    return 0;
}