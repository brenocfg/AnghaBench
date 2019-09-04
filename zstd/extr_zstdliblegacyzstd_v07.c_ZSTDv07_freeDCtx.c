#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  opaque; int /*<<< orphan*/  (* customFree ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;
struct TYPE_6__ {TYPE_1__ customMem; } ;
typedef  TYPE_2__ ZSTDv07_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 

size_t ZSTDv07_freeDCtx(ZSTDv07_DCtx* dctx)
{
    if (dctx==NULL) return 0;   /* support free on NULL */
    dctx->customMem.customFree(dctx->customMem.opaque, dctx);
    return 0;   /* reserved as a potential error code in the future */
}