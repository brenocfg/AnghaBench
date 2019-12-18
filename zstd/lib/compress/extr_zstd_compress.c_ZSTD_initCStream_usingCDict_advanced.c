#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_frameParameters ;
struct TYPE_7__ {int /*<<< orphan*/  fParams; } ;
struct TYPE_8__ {TYPE_1__ requestedParams; } ;
typedef  TYPE_2__ ZSTD_CStream ;
typedef  int /*<<< orphan*/  ZSTD_CDict ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*) ; 
 int /*<<< orphan*/  FORWARD_IF_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_CCtx_refCDict (TYPE_2__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ZSTD_CCtx_reset (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_CCtx_setPledgedSrcSize (TYPE_2__*,unsigned long long) ; 
 int /*<<< orphan*/  ZSTD_reset_session_only ; 

size_t ZSTD_initCStream_usingCDict_advanced(ZSTD_CStream* zcs,
                                            const ZSTD_CDict* cdict,
                                            ZSTD_frameParameters fParams,
                                            unsigned long long pledgedSrcSize)
{
    DEBUGLOG(4, "ZSTD_initCStream_usingCDict_advanced");
    FORWARD_IF_ERROR( ZSTD_CCtx_reset(zcs, ZSTD_reset_session_only) );
    FORWARD_IF_ERROR( ZSTD_CCtx_setPledgedSrcSize(zcs, pledgedSrcSize) );
    zcs->requestedParams.fParams = fParams;
    FORWARD_IF_ERROR( ZSTD_CCtx_refCDict(zcs, cdict) );
    return 0;
}