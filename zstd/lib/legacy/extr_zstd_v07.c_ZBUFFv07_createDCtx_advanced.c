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
struct TYPE_10__ {int /*<<< orphan*/  opaque; scalar_t__ (* customAlloc ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  customFree; } ;
typedef  TYPE_1__ ZSTDv07_customMem ;
struct TYPE_11__ {int /*<<< orphan*/  stage; int /*<<< orphan*/ * zd; int /*<<< orphan*/  customMem; } ;
typedef  TYPE_2__ ZBUFFv07_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  ZBUFFds_init ; 
 int /*<<< orphan*/  ZBUFFv07_freeDCtx (TYPE_2__*) ; 
 int /*<<< orphan*/ * ZSTDv07_createDCtx_advanced (TYPE_1__) ; 
 TYPE_1__ defaultCustomMem ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int) ; 

ZBUFFv07_DCtx* ZBUFFv07_createDCtx_advanced(ZSTDv07_customMem customMem)
{
    ZBUFFv07_DCtx* zbd;

    if (!customMem.customAlloc && !customMem.customFree)
        customMem = defaultCustomMem;

    if (!customMem.customAlloc || !customMem.customFree)
        return NULL;

    zbd = (ZBUFFv07_DCtx*)customMem.customAlloc(customMem.opaque, sizeof(ZBUFFv07_DCtx));
    if (zbd==NULL) return NULL;
    memset(zbd, 0, sizeof(ZBUFFv07_DCtx));
    memcpy(&zbd->customMem, &customMem, sizeof(ZSTDv07_customMem));
    zbd->zd = ZSTDv07_createDCtx_advanced(customMem);
    if (zbd->zd == NULL) { ZBUFFv07_freeDCtx(zbd); return NULL; }
    zbd->stage = ZBUFFds_init;
    return zbd;
}