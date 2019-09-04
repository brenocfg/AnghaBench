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

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstSize_tooSmall ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 

__attribute__((used)) static size_t ZSTDv07_copyRawBlock(void* dst, size_t dstCapacity, const void* src, size_t srcSize)
{
    if (srcSize > dstCapacity) return ERROR(dstSize_tooSmall);
    memcpy(dst, src, srcSize);
    return srcSize;
}