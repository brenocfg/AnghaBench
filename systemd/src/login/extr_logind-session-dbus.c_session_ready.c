#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* user; int /*<<< orphan*/  scope_job; } ;
struct TYPE_5__ {int /*<<< orphan*/  service_job; } ;
typedef  TYPE_2__ Session ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 

__attribute__((used)) static bool session_ready(Session *s) {
        assert(s);

        /* Returns true when the session is ready, i.e. all jobs we enqueued for it are done (regardless if successful or not) */

        return !s->scope_job &&
                !s->user->service_job;
}