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
typedef  int /*<<< orphan*/  ZSTDv06_DCtx ;
typedef  scalar_t__ U32 ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_readLE32 (void const*) ; 
 scalar_t__ const ZSTDv06_DICT_MAGIC ; 
 scalar_t__ ZSTDv06_isError (size_t) ; 
 size_t ZSTDv06_loadEntropy (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  ZSTDv06_refDictContent (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  dictionary_corrupted ; 

__attribute__((used)) static size_t ZSTDv06_decompress_insertDictionary(ZSTDv06_DCtx* dctx, const void* dict, size_t dictSize)
{
    size_t eSize;
    U32 const magic = MEM_readLE32(dict);
    if (magic != ZSTDv06_DICT_MAGIC) {
        /* pure content mode */
        ZSTDv06_refDictContent(dctx, dict, dictSize);
        return 0;
    }
    /* load entropy tables */
    dict = (const char*)dict + 4;
    dictSize -= 4;
    eSize = ZSTDv06_loadEntropy(dctx, dict, dictSize);
    if (ZSTDv06_isError(eSize)) return ERROR(dictionary_corrupted);

    /* reference dictionary content */
    dict = (const char*)dict + eSize;
    dictSize -= eSize;
    ZSTDv06_refDictContent(dctx, dict, dictSize);

    return 0;
}