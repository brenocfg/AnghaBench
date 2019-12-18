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
typedef  int /*<<< orphan*/  js_State ;

/* Variables and functions */
 int /*<<< orphan*/ * STACK ; 
 int TOP ; 
 int /*<<< orphan*/  js_construct (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_endtry (int /*<<< orphan*/ *) ; 
 scalar_t__ js_try (int /*<<< orphan*/ *) ; 

int js_pconstruct(js_State *J, int n)
{
	int savetop = TOP - n - 2;
	if (js_try(J)) {
		/* clean up the stack to only hold the error object */
		STACK[savetop] = STACK[TOP-1];
		TOP = savetop + 1;
		return 1;
	}
	js_construct(J, n);
	js_endtry(J);
	return 0;
}