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
 double INFINITY ; 
 scalar_t__ isnan (double) ; 
 int js_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pushnumber (int /*<<< orphan*/ *,double) ; 
 double js_tonumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ signbit (double) ; 

__attribute__((used)) static void Math_max(js_State *J)
{
	int i, n = js_gettop(J);
	double x = -INFINITY;
	for (i = 1; i < n; ++i) {
		double y = js_tonumber(J, i);
		if (isnan(y)) {
			x = y;
			break;
		}
		if (signbit(x) == signbit(y))
			x = x > y ? x : y;
		else if (signbit(x))
			x = y;
	}
	js_pushnumber(J, x);
}