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
struct chmcLzxcResetTable {int version; int entry_size; int block_len; scalar_t__ compressed_len; scalar_t__ uncompressed_len; int /*<<< orphan*/  table_offset; scalar_t__ block_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  _CHMC_LZXC_RESETTABLE_V1_LEN ; 

void chmc_reset_table_init(struct chmcLzxcResetTable *reset_table)
{
	reset_table->version = 2;
	reset_table->block_count = 0;
	reset_table->entry_size = 8;
	reset_table->table_offset = _CHMC_LZXC_RESETTABLE_V1_LEN;
	reset_table->uncompressed_len = 0;
	reset_table->compressed_len = 0;
	reset_table->block_len = 0x8000;
}