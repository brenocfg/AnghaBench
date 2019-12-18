#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/ * WriteblockFunc ;
struct TYPE_3__ {int block_min_sz; scalar_t__ block_max_sz; scalar_t__ block_sz; int max_block_nr; int /*<<< orphan*/ * blk_sha1s; int /*<<< orphan*/ * write_block; scalar_t__ block_nr; } ;
typedef  TYPE_1__ CDCFileDescriptor ;

/* Variables and functions */
 scalar_t__ BLOCK_MAX_SZ ; 
 int BLOCK_MIN_SZ ; 
 scalar_t__ BLOCK_SZ ; 
 int CHECKSUM_LENGTH ; 
 scalar_t__ calloc (int,int) ; 
 scalar_t__ default_write_chunk ; 

__attribute__((used)) static int init_cdc_file_descriptor (int fd,
                                     uint64_t file_size,
                                     CDCFileDescriptor *file_descr)
{
    int max_block_nr = 0;
    int block_min_sz = 0;

    file_descr->block_nr = 0;

    if (file_descr->block_min_sz <= 0)
        file_descr->block_min_sz = BLOCK_MIN_SZ;
    if (file_descr->block_max_sz <= 0)
        file_descr->block_max_sz = BLOCK_MAX_SZ;
    if (file_descr->block_sz <= 0)
        file_descr->block_sz = BLOCK_SZ;

    if (file_descr->write_block == NULL)
        file_descr->write_block = (WriteblockFunc)default_write_chunk;

    block_min_sz = file_descr->block_min_sz;
    max_block_nr = ((file_size + block_min_sz - 1) / block_min_sz);
    file_descr->blk_sha1s = (uint8_t *)calloc (sizeof(uint8_t),
                                               max_block_nr * CHECKSUM_LENGTH);
    file_descr->max_block_nr = max_block_nr;

    return 0;
}