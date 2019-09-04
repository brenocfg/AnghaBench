#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* member_0; size_t member_1; size_t member_2; size_t pos; } ;
typedef  TYPE_1__ ZSTD_outBuffer ;
struct TYPE_6__ {void const* member_0; size_t member_1; size_t member_2; size_t pos; } ;
typedef  TYPE_2__ ZSTD_inBuffer ;
typedef  int /*<<< orphan*/  ZSTD_EndDirective ;
typedef  int /*<<< orphan*/  ZSTD_CCtx ;

/* Variables and functions */
 size_t ZSTD_compress_generic (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

size_t ZSTD_compress_generic_simpleArgs (
                            ZSTD_CCtx* cctx,
                            void* dst, size_t dstCapacity, size_t* dstPos,
                      const void* src, size_t srcSize, size_t* srcPos,
                            ZSTD_EndDirective endOp)
{
    ZSTD_outBuffer output = { dst, dstCapacity, *dstPos };
    ZSTD_inBuffer  input  = { src, srcSize, *srcPos };
    /* ZSTD_compress_generic() will check validity of dstPos and srcPos */
    size_t const cErr = ZSTD_compress_generic(cctx, &output, &input, endOp);
    *dstPos = output.pos;
    *srcPos = input.pos;
    return cErr;
}