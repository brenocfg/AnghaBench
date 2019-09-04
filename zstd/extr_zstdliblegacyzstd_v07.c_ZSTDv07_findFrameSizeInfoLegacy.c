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
struct TYPE_3__ {scalar_t__ blockType; } ;
typedef  TYPE_1__ blockProperties_t ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t const ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_readLE32 (void const*) ; 
 int /*<<< orphan*/  ZSTD_errorFrameSizeInfoLegacy (size_t*,unsigned long long*,size_t const) ; 
 size_t ZSTDv07_BLOCKSIZE_ABSOLUTEMAX ; 
 scalar_t__ ZSTDv07_MAGICNUMBER ; 
 size_t ZSTDv07_blockHeaderSize ; 
 size_t ZSTDv07_frameHeaderSize (void const*,size_t) ; 
 size_t ZSTDv07_frameHeaderSize_min ; 
 size_t ZSTDv07_getcBlockSize (int /*<<< orphan*/  const*,size_t,TYPE_1__*) ; 
 scalar_t__ ZSTDv07_isError (size_t const) ; 
 scalar_t__ bt_end ; 
 int /*<<< orphan*/  prefix_unknown ; 
 int /*<<< orphan*/  srcSize_wrong ; 

void ZSTDv07_findFrameSizeInfoLegacy(const void *src, size_t srcSize, size_t* cSize, unsigned long long* dBound)
{
    const BYTE* ip = (const BYTE*)src;
    size_t remainingSize = srcSize;
    size_t nbBlocks = 0;

    /* check */
    if (srcSize < ZSTDv07_frameHeaderSize_min+ZSTDv07_blockHeaderSize) {
        ZSTD_errorFrameSizeInfoLegacy(cSize, dBound, ERROR(srcSize_wrong));
        return;
    }

    /* Frame Header */
    {   size_t const frameHeaderSize = ZSTDv07_frameHeaderSize(src, srcSize);
        if (ZSTDv07_isError(frameHeaderSize)) {
            ZSTD_errorFrameSizeInfoLegacy(cSize, dBound, frameHeaderSize);
            return;
        }
        if (MEM_readLE32(src) != ZSTDv07_MAGICNUMBER) {
            ZSTD_errorFrameSizeInfoLegacy(cSize, dBound, ERROR(prefix_unknown));
            return;
        }
        if (srcSize < frameHeaderSize+ZSTDv07_blockHeaderSize) {
            ZSTD_errorFrameSizeInfoLegacy(cSize, dBound, ERROR(srcSize_wrong));
            return;
        }
        ip += frameHeaderSize; remainingSize -= frameHeaderSize;
    }

    /* Loop on each block */
    while (1) {
        blockProperties_t blockProperties;
        size_t const cBlockSize = ZSTDv07_getcBlockSize(ip, remainingSize, &blockProperties);
        if (ZSTDv07_isError(cBlockSize)) {
            ZSTD_errorFrameSizeInfoLegacy(cSize, dBound, cBlockSize);
            return;
        }

        ip += ZSTDv07_blockHeaderSize;
        remainingSize -= ZSTDv07_blockHeaderSize;

        if (blockProperties.blockType == bt_end) break;

        if (cBlockSize > remainingSize) {
            ZSTD_errorFrameSizeInfoLegacy(cSize, dBound, ERROR(srcSize_wrong));
            return;
        }

        ip += cBlockSize;
        remainingSize -= cBlockSize;
        nbBlocks++;
    }

    *cSize = ip - (const BYTE*)src;
    *dBound = nbBlocks * ZSTDv07_BLOCKSIZE_ABSOLUTEMAX;
}