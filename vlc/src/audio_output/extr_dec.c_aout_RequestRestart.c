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
typedef  int /*<<< orphan*/  audio_output_t ;
struct TYPE_3__ {int /*<<< orphan*/  restart; } ;
typedef  TYPE_1__ aout_owner_t ;

/* Variables and functions */
 TYPE_1__* aout_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_fetch_or_explicit (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_order_release ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,unsigned int) ; 

void aout_RequestRestart (audio_output_t *aout, unsigned mode)
{
    aout_owner_t *owner = aout_owner (aout);
    atomic_fetch_or_explicit(&owner->restart, mode, memory_order_release);
    msg_Dbg (aout, "restart requested (%u)", mode);
}