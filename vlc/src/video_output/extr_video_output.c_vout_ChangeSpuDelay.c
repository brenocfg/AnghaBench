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
struct TYPE_5__ {TYPE_1__* p; } ;
typedef  TYPE_2__ vout_thread_t ;
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_4__ {int spu; int /*<<< orphan*/  dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  spu_SetClockDelay (int,size_t,int /*<<< orphan*/ ) ; 

void vout_ChangeSpuDelay(vout_thread_t *vout, size_t channel_id,
                         vlc_tick_t delay)
{
    assert(!vout->p->dummy);
    assert(vout->p->spu);
    spu_SetClockDelay(vout->p->spu, channel_id, delay);
}