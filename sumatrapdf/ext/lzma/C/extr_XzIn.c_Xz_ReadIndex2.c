#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UInt64 ;
typedef  scalar_t__ UInt32 ;
struct TYPE_12__ {size_t totalSize; size_t unpackSize; } ;
struct TYPE_11__ {size_t numBlocks; size_t numBlocksAllocated; TYPE_3__* blocks; } ;
struct TYPE_10__ {TYPE_3__* (* Alloc ) (TYPE_1__*,int) ;} ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ ISzAlloc ;
typedef  TYPE_2__ CXzStream ;
typedef  TYPE_3__ CXzBlockSizes ;
typedef  scalar_t__ Byte ;

/* Variables and functions */
 scalar_t__ CrcCalc (scalar_t__ const*,size_t) ; 
 scalar_t__ GetUi32 (scalar_t__ const*) ; 
 int /*<<< orphan*/  READ_VARINT_AND_CHECK (scalar_t__ const*,size_t,size_t,size_t*) ; 
 int /*<<< orphan*/  SZ_ERROR_ARCHIVE ; 
 int /*<<< orphan*/  SZ_ERROR_MEM ; 
 int /*<<< orphan*/  SZ_OK ; 
 int /*<<< orphan*/  Xz_Free (TYPE_2__*,TYPE_1__*) ; 
 TYPE_3__* stub1 (TYPE_1__*,int) ; 

__attribute__((used)) static SRes Xz_ReadIndex2(CXzStream *p, const Byte *buf, size_t size, ISzAlloc *alloc)
{
  size_t i, numBlocks, crcStartPos, pos = 1;
  UInt32 crc;

  if (size < 5 || buf[0] != 0)
    return SZ_ERROR_ARCHIVE;

  size -= 4;
  crc = CrcCalc(buf, size);
  if (crc != GetUi32(buf + size))
    return SZ_ERROR_ARCHIVE;

  {
    UInt64 numBlocks64;
    READ_VARINT_AND_CHECK(buf, pos, size, &numBlocks64);
    numBlocks = (size_t)numBlocks64;
    if (numBlocks != numBlocks64 || numBlocks * 2 > size)
      return SZ_ERROR_ARCHIVE;
  }
  
  crcStartPos = pos;
  Xz_Free(p, alloc);
  if (numBlocks != 0)
  {
    p->numBlocks = numBlocks;
    p->numBlocksAllocated = numBlocks;
    p->blocks = alloc->Alloc(alloc, sizeof(CXzBlockSizes) * numBlocks);
    if (p->blocks == 0)
      return SZ_ERROR_MEM;
    for (i = 0; i < numBlocks; i++)
    {
      CXzBlockSizes *block = &p->blocks[i];
      READ_VARINT_AND_CHECK(buf, pos, size, &block->totalSize);
      READ_VARINT_AND_CHECK(buf, pos, size, &block->unpackSize);
      if (block->totalSize == 0)
        return SZ_ERROR_ARCHIVE;
    }
  }
  while ((pos & 3) != 0)
    if (buf[pos++] != 0)
      return SZ_ERROR_ARCHIVE;
  return (pos == size) ? SZ_OK : SZ_ERROR_ARCHIVE;
}