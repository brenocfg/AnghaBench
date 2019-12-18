#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_5__ {scalar_t__ state; int flush_n_restarts; scalar_t__ n_restarts; void* clean_result; void* reload_result; void* result; } ;
typedef  TYPE_1__ Service ;

/* Variables and functions */
 TYPE_1__* SERVICE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SERVICE_DEAD ; 
 scalar_t__ SERVICE_FAILED ; 
 void* SERVICE_SUCCESS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  service_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void service_reset_failed(Unit *u) {
        Service *s = SERVICE(u);

        assert(s);

        if (s->state == SERVICE_FAILED)
                service_set_state(s, SERVICE_DEAD);

        s->result = SERVICE_SUCCESS;
        s->reload_result = SERVICE_SUCCESS;
        s->clean_result = SERVICE_SUCCESS;
        s->n_restarts = 0;
        s->flush_n_restarts = false;
}