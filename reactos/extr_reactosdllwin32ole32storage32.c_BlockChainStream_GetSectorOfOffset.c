#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_5__ {scalar_t__ numBlocks; scalar_t__ indexCacheLen; TYPE_1__* indexCache; } ;
struct TYPE_4__ {scalar_t__ firstOffset; scalar_t__ lastOffset; scalar_t__ firstSector; } ;
typedef  TYPE_2__ BlockChainStream ;

/* Variables and functions */
 scalar_t__ BLOCK_END_OF_CHAIN ; 

__attribute__((used)) static ULONG BlockChainStream_GetSectorOfOffset(BlockChainStream *This, ULONG offset)
{
  ULONG min_offset = 0, max_offset = This->numBlocks-1;
  ULONG min_run = 0, max_run = This->indexCacheLen-1;

  if (offset >= This->numBlocks)
    return BLOCK_END_OF_CHAIN;

  while (min_run < max_run)
  {
    ULONG run_to_check = min_run + (offset - min_offset) * (max_run - min_run) / (max_offset - min_offset);
    if (offset < This->indexCache[run_to_check].firstOffset)
    {
      max_offset = This->indexCache[run_to_check].firstOffset-1;
      max_run = run_to_check-1;
    }
    else if (offset > This->indexCache[run_to_check].lastOffset)
    {
      min_offset = This->indexCache[run_to_check].lastOffset+1;
      min_run = run_to_check+1;
    }
    else
      /* Block is in this run. */
      min_run = max_run = run_to_check;
  }

  return This->indexCache[min_run].firstSector + offset - This->indexCache[min_run].firstOffset;
}