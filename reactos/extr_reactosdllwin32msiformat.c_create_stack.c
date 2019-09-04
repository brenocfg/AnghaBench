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
struct TYPE_4__ {int /*<<< orphan*/  items; } ;
typedef  TYPE_1__ STACK ;

/* Variables and functions */
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* msi_alloc (int) ; 

__attribute__((used)) static STACK *create_stack(void)
{
    STACK *stack = msi_alloc(sizeof(STACK));
    list_init(&stack->items);
    return stack;
}