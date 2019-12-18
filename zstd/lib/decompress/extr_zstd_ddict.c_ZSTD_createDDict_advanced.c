#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_dictLoadMethod_e ;
typedef  int /*<<< orphan*/  ZSTD_dictContentType_e ;
struct TYPE_8__ {int /*<<< orphan*/  customFree; int /*<<< orphan*/  customAlloc; } ;
typedef  TYPE_1__ ZSTD_customMem ;
struct TYPE_9__ {TYPE_1__ cMem; } ;
typedef  TYPE_2__ ZSTD_DDict ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_freeDDict (TYPE_2__* const) ; 
 size_t ZSTD_initDDict_internal (TYPE_2__* const,void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ZSTD_isError (size_t const) ; 
 scalar_t__ ZSTD_malloc (int,TYPE_1__) ; 

ZSTD_DDict* ZSTD_createDDict_advanced(const void* dict, size_t dictSize,
                                      ZSTD_dictLoadMethod_e dictLoadMethod,
                                      ZSTD_dictContentType_e dictContentType,
                                      ZSTD_customMem customMem)
{
    if (!customMem.customAlloc ^ !customMem.customFree) return NULL;

    {   ZSTD_DDict* const ddict = (ZSTD_DDict*) ZSTD_malloc(sizeof(ZSTD_DDict), customMem);
        if (ddict == NULL) return NULL;
        ddict->cMem = customMem;
        {   size_t const initResult = ZSTD_initDDict_internal(ddict,
                                            dict, dictSize,
                                            dictLoadMethod, dictContentType);
            if (ZSTD_isError(initResult)) {
                ZSTD_freeDDict(ddict);
                return NULL;
        }   }
        return ddict;
    }
}