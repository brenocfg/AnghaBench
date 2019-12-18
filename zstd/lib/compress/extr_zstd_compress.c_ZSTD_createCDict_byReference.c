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
typedef  int /*<<< orphan*/  ZSTD_compressionParameters ;
typedef  int /*<<< orphan*/  ZSTD_CDict ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_CONTENTSIZE_UNKNOWN ; 
 int /*<<< orphan*/ * ZSTD_createCDict_advanced (void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_dct_auto ; 
 int /*<<< orphan*/  ZSTD_defaultCMem ; 
 int /*<<< orphan*/  ZSTD_dlm_byRef ; 
 int /*<<< orphan*/  ZSTD_getCParams_internal (int,int /*<<< orphan*/ ,size_t) ; 

ZSTD_CDict* ZSTD_createCDict_byReference(const void* dict, size_t dictSize, int compressionLevel)
{
    ZSTD_compressionParameters cParams = ZSTD_getCParams_internal(compressionLevel, ZSTD_CONTENTSIZE_UNKNOWN, dictSize);
    return ZSTD_createCDict_advanced(dict, dictSize,
                                     ZSTD_dlm_byRef, ZSTD_dct_auto,
                                     cParams, ZSTD_defaultCMem);
}