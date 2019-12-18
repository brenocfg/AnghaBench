#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int start; } ;
struct TYPE_5__ {int block_count; int /*<<< orphan*/  compressed_len; scalar_t__ table_offset; } ;
struct TYPE_4__ {scalar_t__ start; } ;
struct chmFile {int data_offset; TYPE_3__ cn_unit; TYPE_2__ reset_table; TYPE_1__ rt_unit; } ;
typedef  int UInt64 ;
typedef  int /*<<< orphan*/  UChar ;
typedef  int /*<<< orphan*/  Int64 ;

/* Variables and functions */
 unsigned int _chm_fetch_bytes (struct chmFile*,int /*<<< orphan*/ *,int,unsigned int) ; 
 int /*<<< orphan*/  _unmarshal_int64 (int /*<<< orphan*/ **,unsigned int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _unmarshal_uint64 (int /*<<< orphan*/ **,unsigned int*,int*) ; 

__attribute__((used)) static int _chm_get_cmpblock_bounds(struct chmFile *h,
                             UInt64 block,
                             UInt64 *start,
                             Int64 *len)
{
    UChar buffer[8], *dummy;
    unsigned int remain;

    /* for all but the last block, use the reset table */
    if (block < h->reset_table.block_count-1)
    {
        /* unpack the start address */
        dummy = buffer;
        remain = 8;
        if (_chm_fetch_bytes(h, buffer,
                             (UInt64)h->data_offset
                                + (UInt64)h->rt_unit.start
                                + (UInt64)h->reset_table.table_offset
                                + (UInt64)block*8,
                             remain) != remain                            ||
            !_unmarshal_uint64(&dummy, &remain, start))
            return 0;

        /* unpack the end address */
        dummy = buffer;
        remain = 8;
        if (_chm_fetch_bytes(h, buffer,
                         (UInt64)h->data_offset
                                + (UInt64)h->rt_unit.start
                                + (UInt64)h->reset_table.table_offset
                                + (UInt64)block*8 + 8,
                         remain) != remain                                ||
            !_unmarshal_int64(&dummy, &remain, len))
            return 0;
    }

    /* for the last block, use the span in addition to the reset table */
    else
    {
        /* unpack the start address */
        dummy = buffer;
        remain = 8;
        if (_chm_fetch_bytes(h, buffer,
                             (UInt64)h->data_offset
                                + (UInt64)h->rt_unit.start
                                + (UInt64)h->reset_table.table_offset
                                + (UInt64)block*8,
                             remain) != remain                            ||
            !_unmarshal_uint64(&dummy, &remain, start))
            return 0;

        *len = h->reset_table.compressed_len;
    }

    /* compute the length and absolute start address */
    *len -= *start;
    *start += h->data_offset + h->cn_unit.start;

    return 1;
}