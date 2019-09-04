#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int litEntropy; int fseEntropy; int /*<<< orphan*/  entropy; void* dictID; } ;
typedef  TYPE_1__ ZSTD_DCtx ;
typedef  scalar_t__ U32 ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 void* MEM_readLE32 (char const*) ; 
 int ZSTD_FRAMEIDSIZE ; 
 scalar_t__ const ZSTD_MAGIC_DICTIONARY ; 
 scalar_t__ ZSTD_isError (size_t const) ; 
 size_t ZSTD_loadEntropy (int /*<<< orphan*/ *,void const*,size_t) ; 
 size_t ZSTD_refDictContent (TYPE_1__*,void const*,size_t) ; 
 int /*<<< orphan*/  dictionary_corrupted ; 

__attribute__((used)) static size_t ZSTD_decompress_insertDictionary(ZSTD_DCtx* dctx, const void* dict, size_t dictSize)
{
    if (dictSize < 8) return ZSTD_refDictContent(dctx, dict, dictSize);
    {   U32 const magic = MEM_readLE32(dict);
        if (magic != ZSTD_MAGIC_DICTIONARY) {
            return ZSTD_refDictContent(dctx, dict, dictSize);   /* pure content mode */
    }   }
    dctx->dictID = MEM_readLE32((const char*)dict + ZSTD_FRAMEIDSIZE);

    /* load entropy tables */
    {   size_t const eSize = ZSTD_loadEntropy(&dctx->entropy, dict, dictSize);
        if (ZSTD_isError(eSize)) return ERROR(dictionary_corrupted);
        dict = (const char*)dict + eSize;
        dictSize -= eSize;
    }
    dctx->litEntropy = dctx->fseEntropy = 1;

    /* reference dictionary content */
    return ZSTD_refDictContent(dctx, dict, dictSize);
}