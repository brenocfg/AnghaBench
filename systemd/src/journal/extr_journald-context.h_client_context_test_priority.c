#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ log_level_max; } ;
typedef  TYPE_1__ ClientContext ;

/* Variables and functions */
 scalar_t__ LOG_PRI (int) ; 

__attribute__((used)) static inline bool client_context_test_priority(const ClientContext *c, int priority) {
        if (!c)
                return true;

        if (c->log_level_max < 0)
                return true;

        return LOG_PRI(priority) <= c->log_level_max;
}