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
struct TYPE_3__ {size_t headerSize; } ;
typedef  TYPE_1__ ZSTDv05_DCtx ;
typedef  scalar_t__ U32 ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_readLE32 (void const*) ; 
 scalar_t__ ZSTDv05_MAGICNUMBER ; 
 size_t ZSTDv05_frameHeaderSize_min ; 
 int /*<<< orphan*/  prefix_unknown ; 
 int /*<<< orphan*/  srcSize_wrong ; 

__attribute__((used)) static size_t ZSTDv05_decodeFrameHeader_Part1(ZSTDv05_DCtx* zc, const void* src, size_t srcSize)
{
    U32 magicNumber;
    if (srcSize != ZSTDv05_frameHeaderSize_min)
        return ERROR(srcSize_wrong);
    magicNumber = MEM_readLE32(src);
    if (magicNumber != ZSTDv05_MAGICNUMBER) return ERROR(prefix_unknown);
    zc->headerSize = ZSTDv05_frameHeaderSize_min;
    return zc->headerSize;
}