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
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_4__ {scalar_t__ pid; scalar_t__ code; int status; int /*<<< orphan*/  exit_timestamp; } ;
struct TYPE_5__ {TYPE_1__ main_exec_status; } ;
typedef  TYPE_2__ Service ;

/* Variables and functions */
 scalar_t__ CLD_EXITED ; 
 int EBADE ; 
 int ENODATA ; 
 TYPE_2__* SERVICE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dual_timestamp_is_set (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int service_exit_status(Unit *u) {
        Service *s = SERVICE(u);

        assert(u);

        if (s->main_exec_status.pid <= 0 ||
            !dual_timestamp_is_set(&s->main_exec_status.exit_timestamp))
                return -ENODATA;

        if (s->main_exec_status.code != CLD_EXITED)
                return -EBADE;

        return s->main_exec_status.status;
}