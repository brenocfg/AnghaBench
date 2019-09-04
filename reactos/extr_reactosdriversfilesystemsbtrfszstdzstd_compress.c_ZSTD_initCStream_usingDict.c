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
struct TYPE_4__ {int /*<<< orphan*/  requestedParams; } ;
typedef  TYPE_1__ ZSTD_CStream ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_CCtxParams_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ZSTD_CONTENTSIZE_UNKNOWN ; 
 size_t ZSTD_initCStream_internal (TYPE_1__*,void const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

size_t ZSTD_initCStream_usingDict(ZSTD_CStream* zcs, const void* dict, size_t dictSize, int compressionLevel)
{
    ZSTD_CCtxParams_init(&zcs->requestedParams, compressionLevel);
    return ZSTD_initCStream_internal(zcs, dict, dictSize, NULL, zcs->requestedParams, ZSTD_CONTENTSIZE_UNKNOWN);
}