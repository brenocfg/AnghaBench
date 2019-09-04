#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  customFree; int /*<<< orphan*/  customAlloc; } ;
typedef  TYPE_1__ ZSTD_customMem ;
struct TYPE_8__ {TYPE_1__ customMem; } ;
typedef  TYPE_2__ ZSTD_CCtx ;

/* Variables and functions */
 scalar_t__ ZSTD_malloc (int,TYPE_1__) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ZSTD_CCtx *ZSTD_createCCtx_advanced(ZSTD_customMem customMem)
{
	ZSTD_CCtx *cctx;
	if (!customMem.customAlloc || !customMem.customFree)
		return NULL;
	cctx = (ZSTD_CCtx *)ZSTD_malloc(sizeof(ZSTD_CCtx), customMem);
	if (!cctx)
		return NULL;
	memset(cctx, 0, sizeof(ZSTD_CCtx));
	cctx->customMem = customMem;
	return cctx;
}