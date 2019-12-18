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
 int /*<<< orphan*/  FORWARD_IF_ERROR (size_t const) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_CCtx_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t ZSTD_compressStream2_simpleArgs (int /*<<< orphan*/ *,void*,size_t,size_t*,void const*,size_t,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_e_end ; 
 int /*<<< orphan*/  ZSTD_reset_session_only ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dstSize_tooSmall ; 

size_t ZSTD_compress2(ZSTD_CCtx* cctx,
                      void* dst, size_t dstCapacity,
                      const void* src, size_t srcSize)
{
    ZSTD_CCtx_reset(cctx, ZSTD_reset_session_only);
    {   size_t oPos = 0;
        size_t iPos = 0;
        size_t const result = ZSTD_compressStream2_simpleArgs(cctx,
                                        dst, dstCapacity, &oPos,
                                        src, srcSize, &iPos,
                                        ZSTD_e_end);
        FORWARD_IF_ERROR(result);
        if (result != 0) {  /* compression not completed, due to lack of output space */
            assert(oPos == dstCapacity);
            RETURN_ERROR(dstSize_tooSmall);
        }
        assert(iPos == srcSize);   /* all input is expected consumed */
        return oPos;
    }
}