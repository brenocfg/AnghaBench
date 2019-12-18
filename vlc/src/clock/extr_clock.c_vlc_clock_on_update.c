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
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_5__ {int /*<<< orphan*/  cbs_data; TYPE_1__* cbs; } ;
typedef  TYPE_2__ vlc_clock_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* on_update ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,unsigned int,unsigned int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void vlc_clock_on_update(vlc_clock_t *clock,
                                       vlc_tick_t system_now,
                                       vlc_tick_t ts, double rate,
                                       unsigned frame_rate,
                                       unsigned frame_rate_base)
{
    if (clock->cbs)
        clock->cbs->on_update(system_now, ts, rate, frame_rate, frame_rate_base,
                              clock->cbs_data);
}