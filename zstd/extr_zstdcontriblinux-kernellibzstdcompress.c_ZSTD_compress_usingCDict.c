#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_3__* refContext; } ;
typedef  TYPE_6__ ZSTD_CDict ;
struct TYPE_16__ {int contentSizeFlag; } ;
struct TYPE_17__ {TYPE_4__ fParams; } ;
struct TYPE_19__ {size_t frameContentSize; TYPE_5__ params; } ;
typedef  TYPE_7__ ZSTD_CCtx ;
struct TYPE_13__ {int contentSizeFlag; } ;
struct TYPE_14__ {TYPE_1__ fParams; } ;
struct TYPE_15__ {TYPE_2__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_F (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_compressBegin_usingCDict (TYPE_7__*,TYPE_6__ const*,size_t) ; 
 size_t ZSTD_compressEnd (TYPE_7__*,void*,size_t,void const*,size_t) ; 

size_t ZSTD_compress_usingCDict(ZSTD_CCtx *cctx, void *dst, size_t dstCapacity, const void *src, size_t srcSize, const ZSTD_CDict *cdict)
{
	CHECK_F(ZSTD_compressBegin_usingCDict(cctx, cdict, srcSize));

	if (cdict->refContext->params.fParams.contentSizeFlag == 1) {
		cctx->params.fParams.contentSizeFlag = 1;
		cctx->frameContentSize = srcSize;
	} else {
		cctx->params.fParams.contentSizeFlag = 0;
	}

	return ZSTD_compressEnd(cctx, dst, dstCapacity, src, srcSize);
}