#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* z_streamp ;
struct TYPE_5__ {unsigned long long pledgedSrcSize; int /*<<< orphan*/  comprState; } ;
typedef  TYPE_2__ ZWRAP_CCtx ;
struct TYPE_4__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZWRAP_useInit ; 
 int Z_OK ; 
 int Z_STREAM_ERROR ; 

int ZWRAP_setPledgedSrcSize(z_streamp strm, unsigned long long pledgedSrcSize)
{
    ZWRAP_CCtx* zwc = (ZWRAP_CCtx*) strm->state;
    if (zwc == NULL) return Z_STREAM_ERROR;

    zwc->pledgedSrcSize = pledgedSrcSize;
    zwc->comprState = ZWRAP_useInit;
    return Z_OK;
}