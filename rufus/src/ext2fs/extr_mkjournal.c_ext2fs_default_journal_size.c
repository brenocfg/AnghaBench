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
typedef  int __u64 ;

/* Variables and functions */

int ext2fs_default_journal_size(__u64 num_blocks)
{
	if (num_blocks < 2048)
		return -1;
	if (num_blocks < 32768)		/* 128 MB */
		return (1024);			/* 4 MB */
	if (num_blocks < 256*1024)	/* 1 GB */
		return (4096);			/* 16 MB */
	if (num_blocks < 512*1024)	/* 2 GB */
		return (8192);			/* 32 MB */
	if (num_blocks < 4096*1024)	/* 16 GB */
		return (16384);			/* 64 MB */
	if (num_blocks < 8192*1024)	/* 32 GB */
		return (32768);			/* 128 MB */
	if (num_blocks < 16384*1024)	/* 64 GB */
		return (65536);			/* 256 MB */
	if (num_blocks < 32768*1024)	/* 128 GB */
		return (131072);		/* 512 MB */
	return 262144;				/* 1 GB */
}