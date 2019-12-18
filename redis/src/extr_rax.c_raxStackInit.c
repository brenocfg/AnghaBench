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
struct TYPE_3__ {scalar_t__ oom; int /*<<< orphan*/  maxitems; scalar_t__ items; int /*<<< orphan*/  static_items; int /*<<< orphan*/  stack; } ;
typedef  TYPE_1__ raxStack ;

/* Variables and functions */
 int /*<<< orphan*/  RAX_STACK_STATIC_ITEMS ; 

__attribute__((used)) static inline void raxStackInit(raxStack *ts) {
    ts->stack = ts->static_items;
    ts->items = 0;
    ts->maxitems = RAX_STACK_STATIC_ITEMS;
    ts->oom = 0;
}