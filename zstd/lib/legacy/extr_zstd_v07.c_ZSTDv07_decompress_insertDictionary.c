#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* dictID; } ;
typedef  TYPE_1__ ZSTDv07_DCtx ;
typedef  scalar_t__ U32 ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 void* MEM_readLE32 (char const*) ; 
 scalar_t__ const ZSTDv07_DICT_MAGIC ; 
 scalar_t__ ZSTDv07_isError (size_t const) ; 
 size_t ZSTDv07_loadEntropy (TYPE_1__*,void const*,size_t) ; 
 size_t ZSTDv07_refDictContent (TYPE_1__*,void const*,size_t) ; 
 int /*<<< orphan*/  dictionary_corrupted ; 

__attribute__((used)) static size_t ZSTDv07_decompress_insertDictionary(ZSTDv07_DCtx* dctx, const void* dict, size_t dictSize)
{
    if (dictSize < 8) return ZSTDv07_refDictContent(dctx, dict, dictSize);
    {   U32 const magic = MEM_readLE32(dict);
        if (magic != ZSTDv07_DICT_MAGIC) {
            return ZSTDv07_refDictContent(dctx, dict, dictSize);   /* pure content mode */
    }   }
    dctx->dictID = MEM_readLE32((const char*)dict + 4);

    /* load entropy tables */
    dict = (const char*)dict + 8;
    dictSize -= 8;
    {   size_t const eSize = ZSTDv07_loadEntropy(dctx, dict, dictSize);
        if (ZSTDv07_isError(eSize)) return ERROR(dictionary_corrupted);
        dict = (const char*)dict + eSize;
        dictSize -= eSize;
    }

    /* reference dictionary content */
    return ZSTDv07_refDictContent(dctx, dict, dictSize);
}