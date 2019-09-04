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
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;

/* Variables and functions */
 int /*<<< orphan*/ * stack_top_ref (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static inline jsval_t stack_topn(script_ctx_t *ctx, unsigned n)
{
    return *stack_top_ref(ctx, n);
}