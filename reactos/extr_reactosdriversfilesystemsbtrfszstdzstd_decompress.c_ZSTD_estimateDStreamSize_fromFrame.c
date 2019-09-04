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
struct TYPE_3__ {scalar_t__ const windowSize; } ;
typedef  TYPE_1__ ZSTD_frameHeader ;
typedef  scalar_t__ U32 ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 unsigned int ZSTD_WINDOWLOG_MAX ; 
 size_t ZSTD_estimateDStreamSize (size_t) ; 
 size_t ZSTD_getFrameHeader (TYPE_1__*,void const*,size_t) ; 
 scalar_t__ ZSTD_isError (size_t const) ; 
 int /*<<< orphan*/  frameParameter_windowTooLarge ; 
 int /*<<< orphan*/  srcSize_wrong ; 

size_t ZSTD_estimateDStreamSize_fromFrame(const void* src, size_t srcSize)
{
    U32 const windowSizeMax = 1U << ZSTD_WINDOWLOG_MAX;   /* note : should be user-selectable */
    ZSTD_frameHeader zfh;
    size_t const err = ZSTD_getFrameHeader(&zfh, src, srcSize);
    if (ZSTD_isError(err)) return err;
    if (err>0) return ERROR(srcSize_wrong);
    if (zfh.windowSize > windowSizeMax)
        return ERROR(frameParameter_windowTooLarge);
    return ZSTD_estimateDStreamSize((size_t)zfh.windowSize);
}