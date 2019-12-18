#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  calendar_spec; } ;
typedef  TYPE_1__ TimerValue ;
struct TYPE_9__ {TYPE_1__* values; } ;
typedef  TYPE_2__ Timer ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  calendar_spec_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  value ; 

void timer_free_values(Timer *t) {
        TimerValue *v;

        assert(t);

        while ((v = t->values)) {
                LIST_REMOVE(value, t->values, v);
                calendar_spec_free(v->calendar_spec);
                free(v);
        }
}