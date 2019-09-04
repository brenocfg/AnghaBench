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
typedef  int /*<<< orphan*/  ppc_trap_frame_t ;

/* Variables and functions */
 scalar_t__ Continue ; 
 int /*<<< orphan*/  PacketWriteSignal (int) ; 
 int /*<<< orphan*/ * RegisterSaveArea ; 
 scalar_t__ SendSignal ; 
 int /*<<< orphan*/  SerialInterrupt (int,int /*<<< orphan*/ *) ; 
 int Signal ; 

int TakeException(int n, ppc_trap_frame_t *tf)
{
    Signal = n;
    RegisterSaveArea = tf;
    PacketWriteSignal(Signal);
    SendSignal = 0;
    Continue = 0;
    while(!Continue) SerialInterrupt(n, tf);
    return 1;
}