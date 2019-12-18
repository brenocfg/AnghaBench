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
 int /*<<< orphan*/  JS_HNUMBER ; 
 scalar_t__ isnan (double) ; 
 scalar_t__ js_isstring (int /*<<< orphan*/ *,int) ; 
 double js_tonumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_toprimitive (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_tostring (int /*<<< orphan*/ *,int) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int js_compare(js_State *J, int *okay)
{
	js_toprimitive(J, -2, JS_HNUMBER);
	js_toprimitive(J, -1, JS_HNUMBER);

	*okay = 1;
	if (js_isstring(J, -2) && js_isstring(J, -1)) {
		return strcmp(js_tostring(J, -2), js_tostring(J, -1));
	} else {
		double x = js_tonumber(J, -2);
		double y = js_tonumber(J, -1);
		if (isnan(x) || isnan(y))
			*okay = 0;
		return x < y ? -1 : x > y ? 1 : 0;
	}
}