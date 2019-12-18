#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  params ;
typedef  scalar_t__ ZSTD_dictLoadMethod_e ;
typedef  scalar_t__ ZSTD_dictContentType_e ;
typedef  void* ZSTD_compressionParameters ;
struct TYPE_12__ {void* cParams; } ;
struct TYPE_10__ {size_t dictContentSize; scalar_t__ dictID; scalar_t__* entropyWorkspace; void const* dictContent; int /*<<< orphan*/  workspace; TYPE_5__ matchState; int /*<<< orphan*/  cBlockState; } ;
typedef  TYPE_2__ ZSTD_CDict ;
struct TYPE_9__ {int contentSizeFlag; } ;
struct TYPE_11__ {void* cParams; TYPE_1__ fParams; int /*<<< orphan*/  compressionLevel; } ;
typedef  TYPE_3__ ZSTD_CCtx_params ;
typedef  scalar_t__ U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,unsigned int) ; 
 int /*<<< orphan*/  FORWARD_IF_ERROR (size_t const) ; 
 int /*<<< orphan*/  HUF_WORKSPACE_SIZE ; 
 int /*<<< orphan*/  RETURN_ERROR_IF (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_CLEVEL_DEFAULT ; 
 int /*<<< orphan*/  ZSTD_checkCParams (void*) ; 
 size_t ZSTD_compress_insertDictionary (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *,TYPE_3__*,void const*,size_t,scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  ZSTD_cwksp_align (size_t,int) ; 
 void* ZSTD_cwksp_reserve_object (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ZSTD_dlm_byRef ; 
 int /*<<< orphan*/  ZSTD_dtlm_full ; 
 int /*<<< orphan*/  ZSTD_resetTarget_CDict ; 
 int /*<<< orphan*/  ZSTD_reset_compressedBlockState (int /*<<< orphan*/ *) ; 
 size_t const ZSTD_reset_matchState (TYPE_5__*,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTDcrp_makeClean ; 
 int /*<<< orphan*/  ZSTDirp_reset ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 
 int /*<<< orphan*/  memory_allocation ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static size_t ZSTD_initCDict_internal(
                    ZSTD_CDict* cdict,
              const void* dictBuffer, size_t dictSize,
                    ZSTD_dictLoadMethod_e dictLoadMethod,
                    ZSTD_dictContentType_e dictContentType,
                    ZSTD_compressionParameters cParams)
{
    DEBUGLOG(3, "ZSTD_initCDict_internal (dictContentType:%u)", (unsigned)dictContentType);
    assert(!ZSTD_checkCParams(cParams));
    cdict->matchState.cParams = cParams;
    if ((dictLoadMethod == ZSTD_dlm_byRef) || (!dictBuffer) || (!dictSize)) {
        cdict->dictContent = dictBuffer;
    } else {
         void *internalBuffer = ZSTD_cwksp_reserve_object(&cdict->workspace, ZSTD_cwksp_align(dictSize, sizeof(void*)));
        RETURN_ERROR_IF(!internalBuffer, memory_allocation);
        cdict->dictContent = internalBuffer;
        memcpy(internalBuffer, dictBuffer, dictSize);
    }
    cdict->dictContentSize = dictSize;

    cdict->entropyWorkspace = (U32*)ZSTD_cwksp_reserve_object(&cdict->workspace, HUF_WORKSPACE_SIZE);


    /* Reset the state to no dictionary */
    ZSTD_reset_compressedBlockState(&cdict->cBlockState);
    FORWARD_IF_ERROR(ZSTD_reset_matchState(
        &cdict->matchState,
        &cdict->workspace,
        &cParams,
        ZSTDcrp_makeClean,
        ZSTDirp_reset,
        ZSTD_resetTarget_CDict));
    /* (Maybe) load the dictionary
     * Skips loading the dictionary if it is < 8 bytes.
     */
    {   ZSTD_CCtx_params params;
        memset(&params, 0, sizeof(params));
        params.compressionLevel = ZSTD_CLEVEL_DEFAULT;
        params.fParams.contentSizeFlag = 1;
        params.cParams = cParams;
        {   size_t const dictID = ZSTD_compress_insertDictionary(
                    &cdict->cBlockState, &cdict->matchState, &cdict->workspace,
                    &params, cdict->dictContent, cdict->dictContentSize,
                    dictContentType, ZSTD_dtlm_full, cdict->entropyWorkspace);
            FORWARD_IF_ERROR(dictID);
            assert(dictID <= (size_t)(U32)-1);
            cdict->dictID = (U32)dictID;
        }
    }

    return 0;
}