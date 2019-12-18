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
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ vlc_fifo_t ;
typedef  int /*<<< orphan*/  vlc_cond_t ;

/* Variables and functions */
 int vlc_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int vlc_fifo_TimedWaitCond(vlc_fifo_t *fifo, vlc_cond_t *condvar, vlc_tick_t deadline)
{
    return vlc_cond_timedwait(condvar, &fifo->lock, deadline);
}