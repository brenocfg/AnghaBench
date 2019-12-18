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

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 size_t ZSTDv06_decompressBegin (int /*<<< orphan*/ *) ; 
 size_t ZSTDv06_decompress_insertDictionary (int /*<<< orphan*/ *,void const*,size_t) ; 
 scalar_t__ ZSTDv06_isError (size_t const) ; 
 int /*<<< orphan*/  dictionary_corrupted ; 

size_t ZSTDv06_decompressBegin_usingDict(ZSTDv06_DCtx* dctx, const void* dict, size_t dictSize)
{
    { size_t const errorCode = ZSTDv06_decompressBegin(dctx);
      if (ZSTDv06_isError(errorCode)) return errorCode; }

    if (dict && dictSize) {
        size_t const errorCode = ZSTDv06_decompress_insertDictionary(dctx, dict, dictSize);
        if (ZSTDv06_isError(errorCode)) return ERROR(dictionary_corrupted);
    }

    return 0;
}