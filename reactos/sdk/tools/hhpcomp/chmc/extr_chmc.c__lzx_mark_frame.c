#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_3__ {void* compressed_len; void* uncompressed_len; int /*<<< orphan*/  block_count; } ;
struct chmcSection {TYPE_1__ reset_table_header; } ;
struct chmcLzxInfo {TYPE_2__* chm; scalar_t__ todo; scalar_t__ done; } ;
typedef  void* UInt64 ;
struct TYPE_4__ {struct chmcSection** sections; } ;

/* Variables and functions */
 int /*<<< orphan*/  chmc_compressed_add_mark (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  chmc_dump (char*,void*,void*,unsigned long,unsigned long) ; 

__attribute__((used)) static void _lzx_mark_frame(void *arg, uint32_t uncomp, uint32_t comp)
{
	struct chmcLzxInfo *lzx_info = (struct chmcLzxInfo *)arg;
	struct chmcSection *section = lzx_info->chm->sections[1];

	UInt64 compressed;

	chmc_dump( "Aligned data at %d(in compressed stream, %d) (%lu/%lu)\n",
	           uncomp, comp, (unsigned long)lzx_info->done, (unsigned long)lzx_info->todo );

	compressed = comp;

	section->reset_table_header.block_count++;

	chmc_compressed_add_mark( lzx_info->chm, compressed );

	section->reset_table_header.uncompressed_len = uncomp;
	section->reset_table_header.compressed_len = comp;
}