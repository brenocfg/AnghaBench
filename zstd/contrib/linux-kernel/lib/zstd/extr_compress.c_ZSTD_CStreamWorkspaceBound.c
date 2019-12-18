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
struct TYPE_4__ {size_t windowLog; } ;
typedef  TYPE_1__ ZSTD_compressionParameters ;
typedef  int /*<<< orphan*/  ZSTD_CStream ;

/* Variables and functions */
 size_t MIN (int /*<<< orphan*/ ,size_t const) ; 
 size_t ZSTD_ALIGN (size_t const) ; 
 int /*<<< orphan*/  ZSTD_BLOCKSIZE_ABSOLUTEMAX ; 
 size_t ZSTD_CCtxWorkspaceBound (TYPE_1__) ; 
 int ZSTD_compressBound (size_t const) ; 

size_t ZSTD_CStreamWorkspaceBound(ZSTD_compressionParameters cParams)
{
	size_t const inBuffSize = (size_t)1 << cParams.windowLog;
	size_t const blockSize = MIN(ZSTD_BLOCKSIZE_ABSOLUTEMAX, inBuffSize);
	size_t const outBuffSize = ZSTD_compressBound(blockSize) + 1;

	return ZSTD_CCtxWorkspaceBound(cParams) + ZSTD_ALIGN(sizeof(ZSTD_CStream)) + ZSTD_ALIGN(inBuffSize) + ZSTD_ALIGN(outBuffSize);
}