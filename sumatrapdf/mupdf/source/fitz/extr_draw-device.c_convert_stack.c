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
typedef  int /*<<< orphan*/  fz_draw_state ;
struct TYPE_3__ {int top; int /*<<< orphan*/ * stack; } ;
typedef  TYPE_1__ fz_draw_device ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  STACK_CONVERT (char const*) ; 

__attribute__((used)) static fz_draw_state *convert_stack(fz_context *ctx, fz_draw_device *dev, const char *message)
{
	fz_draw_state *state = &dev->stack[dev->top-1];
	STACK_CONVERT(message);
	return state;
}