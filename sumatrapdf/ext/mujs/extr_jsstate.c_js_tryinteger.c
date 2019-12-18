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
 int /*<<< orphan*/  js_endtry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int js_tointeger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_try (int /*<<< orphan*/ *) ; 

int js_tryinteger(js_State *J, int idx, int error)
{
	int v;
	if (js_try(J)) {
		js_pop(J, 1);
		return error;
	}
	v = js_tointeger(J, idx);
	js_endtry(J);
	return v;
}