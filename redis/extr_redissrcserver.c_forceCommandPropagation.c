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
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ client ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_FORCE_AOF ; 
 int /*<<< orphan*/  CLIENT_FORCE_REPL ; 
 int PROPAGATE_AOF ; 
 int PROPAGATE_REPL ; 

void forceCommandPropagation(client *c, int flags) {
    if (flags & PROPAGATE_REPL) c->flags |= CLIENT_FORCE_REPL;
    if (flags & PROPAGATE_AOF) c->flags |= CLIENT_FORCE_AOF;
}