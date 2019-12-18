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
struct TYPE_4__ {struct TYPE_4__* outBuff; struct TYPE_4__* inBuff; int /*<<< orphan*/  zd; } ;
typedef  TYPE_1__ ZBUFFv06_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTDv06_freeDCtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

size_t ZBUFFv06_freeDCtx(ZBUFFv06_DCtx* zbd)
{
    if (zbd==NULL) return 0;   /* support free on null */
    ZSTDv06_freeDCtx(zbd->zd);
    free(zbd->inBuff);
    free(zbd->outBuff);
    free(zbd);
    return 0;
}