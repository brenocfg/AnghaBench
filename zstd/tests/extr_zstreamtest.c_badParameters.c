#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ checksumFlag; scalar_t__ contentSizeFlag; scalar_t__ noDictIDFlag; } ;
struct TYPE_6__ {scalar_t__ windowLog; scalar_t__ hashLog; scalar_t__ chainLog; scalar_t__ searchLog; scalar_t__ minMatch; scalar_t__ targetLength; } ;
struct TYPE_8__ {TYPE_2__ fParams; TYPE_1__ cParams; } ;
typedef  TYPE_3__ ZSTD_parameters ;
typedef  int /*<<< orphan*/  ZSTD_CCtx ;
typedef  int U32 ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_RET (int,int,char*) ; 
 scalar_t__ ZSTD_isError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getCCtxParams (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static U32 badParameters(ZSTD_CCtx* zc, ZSTD_parameters const savedParams)
{
    ZSTD_parameters params;
    if (ZSTD_isError(getCCtxParams(zc, &params))) return 10;
    CHECK_RET(1, params.cParams.windowLog != savedParams.cParams.windowLog, "windowLog");
    CHECK_RET(2, params.cParams.hashLog != savedParams.cParams.hashLog, "hashLog");
    CHECK_RET(3, params.cParams.chainLog != savedParams.cParams.chainLog, "chainLog");
    CHECK_RET(4, params.cParams.searchLog != savedParams.cParams.searchLog, "searchLog");
    CHECK_RET(5, params.cParams.minMatch != savedParams.cParams.minMatch, "minMatch");
    CHECK_RET(6, params.cParams.targetLength != savedParams.cParams.targetLength, "targetLength");

    CHECK_RET(7, params.fParams.checksumFlag != savedParams.fParams.checksumFlag, "checksumFlag");
    CHECK_RET(8, params.fParams.contentSizeFlag != savedParams.fParams.contentSizeFlag, "contentSizeFlag");
    CHECK_RET(9, params.fParams.noDictIDFlag != savedParams.fParams.noDictIDFlag, "noDictIDFlag");
    return 0;
}