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
 int /*<<< orphan*/  DEBUGLOG (int,char*) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETURN_ERROR_IF (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstBuffer_null ; 
 int /*<<< orphan*/  dstSize_tooSmall ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 

__attribute__((used)) static size_t ZSTD_copyRawBlock(void* dst, size_t dstCapacity,
                          const void* src, size_t srcSize)
{
    DEBUGLOG(5, "ZSTD_copyRawBlock");
    if (dst == NULL) {
        if (srcSize == 0) return 0;
        RETURN_ERROR(dstBuffer_null);
    }
    RETURN_ERROR_IF(srcSize > dstCapacity, dstSize_tooSmall);
    memcpy(dst, src, srcSize);
    return srcSize;
}