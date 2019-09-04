#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ dictID; scalar_t__ checksumFlag; } ;
struct TYPE_4__ {scalar_t__ dictID; int /*<<< orphan*/  xxhState; TYPE_2__ fParams; } ;
typedef  TYPE_1__ ZSTDv07_DCtx ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XXH64_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t ZSTDv07_getFrameParams (TYPE_2__*,void const*,size_t) ; 
 int /*<<< orphan*/  dictionary_wrong ; 

__attribute__((used)) static size_t ZSTDv07_decodeFrameHeader(ZSTDv07_DCtx* dctx, const void* src, size_t srcSize)
{
    size_t const result = ZSTDv07_getFrameParams(&(dctx->fParams), src, srcSize);
    if (dctx->fParams.dictID && (dctx->dictID != dctx->fParams.dictID)) return ERROR(dictionary_wrong);
    if (dctx->fParams.checksumFlag) XXH64_reset(&dctx->xxhState, 0);
    return result;
}