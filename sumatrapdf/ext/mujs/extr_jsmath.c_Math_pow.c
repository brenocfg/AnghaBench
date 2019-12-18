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
 int /*<<< orphan*/  NAN ; 
 int fabs (double) ; 
 int /*<<< orphan*/  isfinite (double) ; 
 int /*<<< orphan*/  js_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 double js_tonumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pow (double,double) ; 

__attribute__((used)) static void Math_pow(js_State *J)
{
	double x = js_tonumber(J, 1);
	double y = js_tonumber(J, 2);
	if (!isfinite(y) && fabs(x) == 1)
		js_pushnumber(J, NAN);
	else
		js_pushnumber(J, pow(x,y));
}