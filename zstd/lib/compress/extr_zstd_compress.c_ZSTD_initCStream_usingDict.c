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
typedef  int /*<<< orphan*/  ZSTD_CStream ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*) ; 
 int /*<<< orphan*/  FORWARD_IF_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_CCtx_loadDictionary (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  ZSTD_CCtx_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_CCtx_setParameter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ZSTD_c_compressionLevel ; 
 int /*<<< orphan*/  ZSTD_reset_session_only ; 

size_t ZSTD_initCStream_usingDict(ZSTD_CStream* zcs, const void* dict, size_t dictSize, int compressionLevel)
{
    DEBUGLOG(4, "ZSTD_initCStream_usingDict");
    FORWARD_IF_ERROR( ZSTD_CCtx_reset(zcs, ZSTD_reset_session_only) );
    FORWARD_IF_ERROR( ZSTD_CCtx_setParameter(zcs, ZSTD_c_compressionLevel, compressionLevel) );
    FORWARD_IF_ERROR( ZSTD_CCtx_loadDictionary(zcs, dict, dictSize) );
    return 0;
}