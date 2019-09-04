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
 size_t MIN (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_BLOCKSIZE_MAX ; 
 int /*<<< orphan*/  ZSTD_CONTENTSIZE_UNKNOWN ; 
 size_t ZSTD_decodingBufferSize_min (size_t,int /*<<< orphan*/ ) ; 
 size_t ZSTD_estimateDCtxSize () ; 

size_t ZSTD_estimateDStreamSize(size_t windowSize)
{
    size_t const blockSize = MIN(windowSize, ZSTD_BLOCKSIZE_MAX);
    size_t const inBuffSize = blockSize;  /* no block can be larger */
    size_t const outBuffSize = ZSTD_decodingBufferSize_min(windowSize, ZSTD_CONTENTSIZE_UNKNOWN);
    return ZSTD_estimateDCtxSize() + inBuffSize + outBuffSize;
}