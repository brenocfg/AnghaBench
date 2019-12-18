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
typedef  scalar_t__ ZSTD_dictLoadMethod_e ;
typedef  int /*<<< orphan*/  ZSTD_compressionParameters ;
typedef  int /*<<< orphan*/  ZSTD_CDict ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,unsigned int) ; 
 int HUF_WORKSPACE_SIZE ; 
 int ZSTD_cwksp_align (size_t,int) ; 
 size_t ZSTD_cwksp_alloc_size (int) ; 
 scalar_t__ ZSTD_dlm_byRef ; 
 size_t ZSTD_sizeof_matchState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

size_t ZSTD_estimateCDictSize_advanced(
        size_t dictSize, ZSTD_compressionParameters cParams,
        ZSTD_dictLoadMethod_e dictLoadMethod)
{
    DEBUGLOG(5, "sizeof(ZSTD_CDict) : %u", (unsigned)sizeof(ZSTD_CDict));
    return ZSTD_cwksp_alloc_size(sizeof(ZSTD_CDict))
         + ZSTD_cwksp_alloc_size(HUF_WORKSPACE_SIZE)
         + ZSTD_sizeof_matchState(&cParams, /* forCCtx */ 0)
         + (dictLoadMethod == ZSTD_dlm_byRef ? 0
            : ZSTD_cwksp_alloc_size(ZSTD_cwksp_align(dictSize, sizeof(void *))));
}