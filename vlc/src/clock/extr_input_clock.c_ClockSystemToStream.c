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
struct TYPE_4__ {int system; int stream; } ;
struct TYPE_5__ {int rate; TYPE_1__ ref; int /*<<< orphan*/  b_has_reference; } ;
typedef  TYPE_2__ input_clock_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static vlc_tick_t ClockSystemToStream( input_clock_t *cl, vlc_tick_t i_system )
{
    assert( cl->b_has_reference );
    return (vlc_tick_t) (( i_system - cl->ref.system ) * cl->rate) + cl->ref.stream;
}