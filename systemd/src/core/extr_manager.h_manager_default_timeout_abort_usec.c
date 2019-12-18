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
struct TYPE_4__ {int /*<<< orphan*/  default_timeout_stop_usec; int /*<<< orphan*/  default_timeout_abort_usec; scalar_t__ default_timeout_abort_set; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static inline usec_t manager_default_timeout_abort_usec(Manager *m) {
        assert(m);
        return m->default_timeout_abort_set ? m->default_timeout_abort_usec : m->default_timeout_stop_usec;
}