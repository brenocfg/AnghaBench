#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  customFree; int /*<<< orphan*/  customAlloc; } ;
typedef  TYPE_1__ ZSTD_customMem ;
struct TYPE_11__ {int /*<<< orphan*/ * cctx; int /*<<< orphan*/  customMem; } ;
typedef  TYPE_2__ ZSTD_CStream ;

/* Variables and functions */
 int /*<<< orphan*/ * ZSTD_createCCtx_advanced (TYPE_1__) ; 
 int /*<<< orphan*/  ZSTD_freeCStream (TYPE_2__*) ; 
 scalar_t__ ZSTD_malloc (int,TYPE_1__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

ZSTD_CStream *ZSTD_createCStream_advanced(ZSTD_customMem customMem)
{
	ZSTD_CStream *zcs;

	if (!customMem.customAlloc || !customMem.customFree)
		return NULL;

	zcs = (ZSTD_CStream *)ZSTD_malloc(sizeof(ZSTD_CStream), customMem);
	if (zcs == NULL)
		return NULL;
	memset(zcs, 0, sizeof(ZSTD_CStream));
	memcpy(&zcs->customMem, &customMem, sizeof(ZSTD_customMem));
	zcs->cctx = ZSTD_createCCtx_advanced(customMem);
	if (zcs->cctx == NULL) {
		ZSTD_freeCStream(zcs);
		return NULL;
	}
	return zcs;
}