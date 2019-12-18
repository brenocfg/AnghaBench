#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * ctxs; } ;
typedef  TYPE_1__ opj_mqc_t ;
typedef  size_t OPJ_UINT32 ;

/* Variables and functions */
 size_t MQC_NUMCTXS ; 
 int /*<<< orphan*/  mqc_states ; 

void opj_mqc_resetstates(opj_mqc_t *mqc)
{
    OPJ_UINT32 i;
    for (i = 0; i < MQC_NUMCTXS; i++) {
        mqc->ctxs[i] = mqc_states;
    }
}