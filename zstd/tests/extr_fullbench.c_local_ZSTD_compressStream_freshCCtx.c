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
typedef  int /*<<< orphan*/  ZSTD_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/ * ZSTD_createCCtx () ; 
 int /*<<< orphan*/  ZSTD_freeCCtx (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 size_t local_ZSTD_compressStream (void const*,size_t,void*,size_t,void*) ; 

__attribute__((used)) static size_t
local_ZSTD_compressStream_freshCCtx(const void* src, size_t srcSize,
                          void* dst, size_t dstCapacity,
                          void* payload)
{
    ZSTD_CCtx* const cctx = ZSTD_createCCtx();
    size_t r;
    assert(cctx != NULL);

    r = local_ZSTD_compressStream(src, srcSize, dst, dstCapacity, payload);

    ZSTD_freeCCtx(cctx);

    return r;
}