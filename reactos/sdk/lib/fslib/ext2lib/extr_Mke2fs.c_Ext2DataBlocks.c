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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  PEXT2_FILESYS ;

/* Variables and functions */
 int BLOCK_BITS ; 
 int EXT2_NDIR_BLOCKS ; 

ULONG
Ext2DataBlocks(PEXT2_FILESYS Ext2Sys, ULONG TotalBlocks)
{
    ULONG   dwData[4] = {1, 1, 1, 1};
    ULONG   dwMeta[4] = {0, 0, 0, 0};
    ULONG   DataBlocks = 0;
    ULONG   i, j;

    if (TotalBlocks <= EXT2_NDIR_BLOCKS)
    {
        return TotalBlocks;
    }

    TotalBlocks -= EXT2_NDIR_BLOCKS;

    for (i = 0; i < 4; i++)
    {
        dwData[i] = dwData[i] << ((BLOCK_BITS - 2) * i);

        if (i > 0)
        {
            dwMeta[i] = 1 + (dwMeta[i - 1] << (BLOCK_BITS - 2));
        }
    }

    for( i=1; (i < 4) && (TotalBlocks > 0); i++)
    {
        if (TotalBlocks >= (dwData[i] + dwMeta[i]))
        {
            TotalBlocks -= (dwData[i] + dwMeta[i]);
            DataBlocks  += dwData[i];
        }
        else
        {
            ULONG   dwDivide = 0;
            ULONG   dwRemain = 0;

            for (j=i; (j > 0) && (TotalBlocks > 0); j--)
            {
                dwDivide = (TotalBlocks - 1) / (dwData[j-1] + dwMeta[j-1]);
                dwRemain = (TotalBlocks - 1) % (dwData[j-1] + dwMeta[j-1]);

                DataBlocks += (dwDivide * dwData[j-1]);
                TotalBlocks = dwRemain;
            }
        }
    }

    return (DataBlocks + EXT2_NDIR_BLOCKS);
}