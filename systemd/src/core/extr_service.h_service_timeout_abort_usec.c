#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usec_t ;
struct TYPE_4__ {int /*<<< orphan*/  timeout_stop_usec; int /*<<< orphan*/  timeout_abort_usec; scalar_t__ timeout_abort_set; } ;
typedef  TYPE_1__ Service ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static inline usec_t service_timeout_abort_usec(Service *s) {
        assert(s);
        return s->timeout_abort_set ? s->timeout_abort_usec : s->timeout_stop_usec;
}