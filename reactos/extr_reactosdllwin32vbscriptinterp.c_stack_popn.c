#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  exec_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_pop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stack_popn(exec_ctx_t *ctx, unsigned n)
{
    while(n--)
        VariantClear(stack_pop(ctx));
}