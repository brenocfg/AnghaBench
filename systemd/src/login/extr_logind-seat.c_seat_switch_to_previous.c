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
struct TYPE_5__ {int position_count; scalar_t__* positions; TYPE_1__* active; } ;
struct TYPE_4__ {unsigned int position; } ;
typedef  TYPE_2__ Seat ;

/* Variables and functions */
 int EINVAL ; 
 int session_activate (scalar_t__) ; 

int seat_switch_to_previous(Seat *s) {
        unsigned start, i;

        if (s->position_count == 0)
                return -EINVAL;

        start = 1;
        if (s->active && s->active->position > 0)
                start = s->active->position;

        for (i = start - 1; i > 0; --i)
                if (s->positions[i])
                        return session_activate(s->positions[i]);

        for (i = s->position_count - 1; i > start; --i)
                if (s->positions[i])
                        return session_activate(s->positions[i]);

        return -EINVAL;
}