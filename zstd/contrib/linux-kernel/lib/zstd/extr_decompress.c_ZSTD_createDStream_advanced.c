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
struct TYPE_11__ {int /*<<< orphan*/  maxWindowSize; int /*<<< orphan*/  stage; int /*<<< orphan*/ * dctx; int /*<<< orphan*/  customMem; } ;
typedef  TYPE_2__ ZSTD_DStream ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_MAXWINDOWSIZE_DEFAULT ; 
 int /*<<< orphan*/ * ZSTD_createDCtx_advanced (TYPE_1__) ; 
 int /*<<< orphan*/  ZSTD_freeDStream (TYPE_2__*) ; 
 scalar_t__ ZSTD_malloc (int,TYPE_1__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zdss_init ; 

__attribute__((used)) static ZSTD_DStream *ZSTD_createDStream_advanced(ZSTD_customMem customMem)
{
	ZSTD_DStream *zds;

	if (!customMem.customAlloc || !customMem.customFree)
		return NULL;

	zds = (ZSTD_DStream *)ZSTD_malloc(sizeof(ZSTD_DStream), customMem);
	if (zds == NULL)
		return NULL;
	memset(zds, 0, sizeof(ZSTD_DStream));
	memcpy(&zds->customMem, &customMem, sizeof(ZSTD_customMem));
	zds->dctx = ZSTD_createDCtx_advanced(customMem);
	if (zds->dctx == NULL) {
		ZSTD_freeDStream(zds);
		return NULL;
	}
	zds->stage = zdss_init;
	zds->maxWindowSize = ZSTD_MAXWINDOWSIZE_DEFAULT;
	return zds;
}