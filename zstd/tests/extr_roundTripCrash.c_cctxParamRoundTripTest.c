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
struct TYPE_5__ {void* member_0; size_t member_1; int /*<<< orphan*/  pos; int /*<<< orphan*/  member_2; } ;
typedef  TYPE_1__ ZSTD_outBuffer ;
struct TYPE_6__ {void const* member_0; size_t member_1; int /*<<< orphan*/  member_2; } ;
typedef  TYPE_2__ ZSTD_inBuffer ;
typedef  int /*<<< orphan*/  ZSTD_CCtx_params ;
typedef  int /*<<< orphan*/  ZSTD_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_Z (int /*<<< orphan*/ ) ; 
 size_t MIN (int,size_t) ; 
 unsigned int XXH32 (void const*,size_t const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_CCtxParams_setParameter (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  ZSTD_CCtx_setParametersUsingCCtxParams (int /*<<< orphan*/ * const,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  ZSTD_c_compressionLevel ; 
 int /*<<< orphan*/  ZSTD_c_nbWorkers ; 
 int /*<<< orphan*/  ZSTD_c_overlapLog ; 
 int /*<<< orphan*/  ZSTD_compressStream2 (int /*<<< orphan*/ * const,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ZSTD_createCCtx () ; 
 int /*<<< orphan*/ * ZSTD_createCCtxParams () ; 
 size_t ZSTD_decompress (void*,size_t,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_e_end ; 
 int /*<<< orphan*/  ZSTD_freeCCtx (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  ZSTD_freeCCtxParams (int /*<<< orphan*/ * const) ; 

__attribute__((used)) static size_t cctxParamRoundTripTest(void* resultBuff, size_t resultBuffCapacity,
                            void* compressedBuff, size_t compressedBuffCapacity,
                      const void* srcBuff, size_t srcBuffSize)
{
    ZSTD_CCtx* const cctx = ZSTD_createCCtx();
    ZSTD_CCtx_params* const cctxParams = ZSTD_createCCtxParams();
    ZSTD_inBuffer inBuffer = { srcBuff, srcBuffSize, 0 };
    ZSTD_outBuffer outBuffer = { compressedBuff, compressedBuffCapacity, 0 };

    static const int maxClevel = 19;
    size_t const hashLength = MIN(128, srcBuffSize);
    unsigned const h32 = XXH32(srcBuff, hashLength, 0);
    int const cLevel = h32 % maxClevel;

    /* Set parameters */
    CHECK_Z( ZSTD_CCtxParams_setParameter(cctxParams, ZSTD_c_compressionLevel, cLevel) );
    CHECK_Z( ZSTD_CCtxParams_setParameter(cctxParams, ZSTD_c_nbWorkers, 2) );
    CHECK_Z( ZSTD_CCtxParams_setParameter(cctxParams, ZSTD_c_overlapLog, 5) );


    /* Apply parameters */
    CHECK_Z( ZSTD_CCtx_setParametersUsingCCtxParams(cctx, cctxParams) );

    CHECK_Z (ZSTD_compressStream2(cctx, &outBuffer, &inBuffer, ZSTD_e_end) );

    ZSTD_freeCCtxParams(cctxParams);
    ZSTD_freeCCtx(cctx);

    return ZSTD_decompress(resultBuff, resultBuffCapacity, compressedBuff, outBuffer.pos);
}