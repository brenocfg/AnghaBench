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
struct TYPE_3__ {scalar_t__ restart_kill_signal; int kill_signal; } ;
typedef  TYPE_1__ KillContext ;

/* Variables and functions */

__attribute__((used)) static inline int restart_kill_signal(const KillContext *c) {
        if (c->restart_kill_signal != 0)
                return c->restart_kill_signal;
        return c->kill_signal;
}