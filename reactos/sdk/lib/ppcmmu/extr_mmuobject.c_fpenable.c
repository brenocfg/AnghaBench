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
struct TYPE_3__ {int srr1; } ;
typedef  TYPE_1__ ppc_trap_frame_t ;

/* Variables and functions */

int fpenable(int trapCode, ppc_trap_frame_t *trap)
{
        /* Turn on FP */
        trap->srr1 |= 8192;
        return 1;
}