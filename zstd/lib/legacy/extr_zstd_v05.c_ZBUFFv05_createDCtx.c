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
struct TYPE_4__ {int /*<<< orphan*/  stage; int /*<<< orphan*/  zc; } ;
typedef  TYPE_1__ ZBUFFv05_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  ZBUFFv05ds_init ; 
 int /*<<< orphan*/  ZSTDv05_createDCtx () ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

ZBUFFv05_DCtx* ZBUFFv05_createDCtx(void)
{
    ZBUFFv05_DCtx* zbc = (ZBUFFv05_DCtx*)malloc(sizeof(ZBUFFv05_DCtx));
    if (zbc==NULL) return NULL;
    memset(zbc, 0, sizeof(*zbc));
    zbc->zc = ZSTDv05_createDCtx();
    zbc->stage = ZBUFFv05ds_init;
    return zbc;
}