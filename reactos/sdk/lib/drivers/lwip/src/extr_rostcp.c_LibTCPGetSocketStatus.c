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
struct TYPE_3__ {scalar_t__ state; } ;
typedef  scalar_t__* PULONG ;
typedef  TYPE_1__* PTCP_PCB ;

/* Variables and functions */

void
LibTCPGetSocketStatus(
    PTCP_PCB pcb,
    PULONG State)
{
    /* Translate state from enum tcp_state -> MIB_TCP_STATE */
    *State = pcb->state + 1;
}