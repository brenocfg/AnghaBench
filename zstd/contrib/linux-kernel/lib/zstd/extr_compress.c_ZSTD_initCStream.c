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
typedef  int /*<<< orphan*/  ZSTD_parameters ;
typedef  int /*<<< orphan*/  ZSTD_customMem ;
typedef  int /*<<< orphan*/  ZSTD_CStream ;

/* Variables and functions */
 int /*<<< orphan*/ * ZSTD_createCStream_advanced (int /*<<< orphan*/  const) ; 
 size_t ZSTD_initCStream_advanced (int /*<<< orphan*/ * const,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  ZSTD_initStack (void*,size_t) ; 
 scalar_t__ ZSTD_isError (size_t const) ; 

ZSTD_CStream *ZSTD_initCStream(ZSTD_parameters params, unsigned long long pledgedSrcSize, void *workspace, size_t workspaceSize)
{
	ZSTD_customMem const stackMem = ZSTD_initStack(workspace, workspaceSize);
	ZSTD_CStream *const zcs = ZSTD_createCStream_advanced(stackMem);
	if (zcs) {
		size_t const code = ZSTD_initCStream_advanced(zcs, NULL, 0, params, pledgedSrcSize);
		if (ZSTD_isError(code)) {
			return NULL;
		}
	}
	return zcs;
}