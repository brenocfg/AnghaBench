#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ Unit ;
struct TYPE_12__ {scalar_t__ result; } ;
typedef  scalar_t__ ServiceResult ;
typedef  TYPE_2__ Service ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 TYPE_2__* SERVICE (TYPE_1__*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert_se (TYPE_1__*) ; 
 int /*<<< orphan*/  log_error (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  service_result_to_string (scalar_t__) ; 
 int /*<<< orphan*/  wait_for_service_finish (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static void check_service_result(const char *func, Manager *m, Unit *unit, ServiceResult result_expected) {
        Service *service = NULL;

        assert_se(m);
        assert_se(unit);

        wait_for_service_finish(m, unit);

        service = SERVICE(unit);

        if (service->result != result_expected) {
                log_error("%s: %s: service end result %s, expected %s",
                          func, unit->id,
                          service_result_to_string(service->result),
                          service_result_to_string(result_expected));
                abort();
        }
}