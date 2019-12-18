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
typedef  int /*<<< orphan*/  ZSTDv05_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTDv05_decompressBegin (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 

ZSTDv05_DCtx* ZSTDv05_createDCtx(void)
{
    ZSTDv05_DCtx* dctx = (ZSTDv05_DCtx*)malloc(sizeof(ZSTDv05_DCtx));
    if (dctx==NULL) return NULL;
    ZSTDv05_decompressBegin(dctx);
    return dctx;
}