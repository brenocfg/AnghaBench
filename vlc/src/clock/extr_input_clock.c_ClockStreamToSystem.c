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
typedef  int vlc_tick_t ;
struct TYPE_4__ {int stream; int system; } ;
struct TYPE_5__ {int rate; TYPE_1__ ref; int /*<<< orphan*/  b_has_reference; } ;
typedef  TYPE_2__ input_clock_t ;

/* Variables and functions */
 int VLC_TICK_INVALID ; 

__attribute__((used)) static vlc_tick_t ClockStreamToSystem( input_clock_t *cl, vlc_tick_t i_stream )
{
    if( !cl->b_has_reference )
        return VLC_TICK_INVALID;

    return (vlc_tick_t) (( i_stream - cl->ref.stream ) / cl->rate) + cl->ref.system;
}