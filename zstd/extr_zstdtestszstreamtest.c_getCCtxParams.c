#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int checksumFlag; int contentSizeFlag; int noDictIDFlag; } ;
struct TYPE_5__ {int strategy; int /*<<< orphan*/  targetLength; int /*<<< orphan*/  minMatch; int /*<<< orphan*/  searchLog; int /*<<< orphan*/  chainLog; int /*<<< orphan*/  hashLog; int /*<<< orphan*/  windowLog; } ;
struct TYPE_7__ {TYPE_2__ fParams; TYPE_1__ cParams; } ;
typedef  TYPE_3__ ZSTD_parameters ;
typedef  int /*<<< orphan*/  ZSTD_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_RET_Z (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_CCtx_getParameter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ZSTD_c_chainLog ; 
 int /*<<< orphan*/  ZSTD_c_checksumFlag ; 
 int /*<<< orphan*/  ZSTD_c_contentSizeFlag ; 
 int /*<<< orphan*/  ZSTD_c_dictIDFlag ; 
 int /*<<< orphan*/  ZSTD_c_hashLog ; 
 int /*<<< orphan*/  ZSTD_c_minMatch ; 
 int /*<<< orphan*/  ZSTD_c_searchLog ; 
 int /*<<< orphan*/  ZSTD_c_strategy ; 
 int /*<<< orphan*/  ZSTD_c_targetLength ; 
 int /*<<< orphan*/  ZSTD_c_windowLog ; 

__attribute__((used)) static size_t getCCtxParams(ZSTD_CCtx* zc, ZSTD_parameters* savedParams)
{
    int value;
    CHECK_RET_Z(ZSTD_CCtx_getParameter(zc, ZSTD_c_windowLog, (int*)&savedParams->cParams.windowLog));
    CHECK_RET_Z(ZSTD_CCtx_getParameter(zc, ZSTD_c_hashLog, (int*)&savedParams->cParams.hashLog));
    CHECK_RET_Z(ZSTD_CCtx_getParameter(zc, ZSTD_c_chainLog, (int*)&savedParams->cParams.chainLog));
    CHECK_RET_Z(ZSTD_CCtx_getParameter(zc, ZSTD_c_searchLog, (int*)&savedParams->cParams.searchLog));
    CHECK_RET_Z(ZSTD_CCtx_getParameter(zc, ZSTD_c_minMatch, (int*)&savedParams->cParams.minMatch));
    CHECK_RET_Z(ZSTD_CCtx_getParameter(zc, ZSTD_c_targetLength, (int*)&savedParams->cParams.targetLength));
    CHECK_RET_Z(ZSTD_CCtx_getParameter(zc, ZSTD_c_strategy, &value));
    savedParams->cParams.strategy = value;

    CHECK_RET_Z(ZSTD_CCtx_getParameter(zc, ZSTD_c_checksumFlag, &savedParams->fParams.checksumFlag));
    CHECK_RET_Z(ZSTD_CCtx_getParameter(zc, ZSTD_c_contentSizeFlag, &savedParams->fParams.contentSizeFlag));
    CHECK_RET_Z(ZSTD_CCtx_getParameter(zc, ZSTD_c_dictIDFlag, &value));
    savedParams->fParams.noDictIDFlag = !value;
    return 0;
}