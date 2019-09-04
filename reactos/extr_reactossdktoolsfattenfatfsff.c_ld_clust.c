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
struct TYPE_3__ {scalar_t__ fs_type; } ;
typedef  TYPE_1__ FATFS ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int DIR_FstClusHI ; 
 int DIR_FstClusLO ; 
 scalar_t__ FS_FAT32 ; 
 int LD_WORD (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static
DWORD ld_clust (	/* Returns the top cluster value of the SFN entry */
	FATFS* fs,		/* Pointer to the fs object */
	const BYTE* dir	/* Pointer to the SFN entry */
)
{
	DWORD cl;

	cl = LD_WORD(dir + DIR_FstClusLO);
	if (fs->fs_type == FS_FAT32)
		cl |= (DWORD)LD_WORD(dir + DIR_FstClusHI) << 16;

	return cl;
}