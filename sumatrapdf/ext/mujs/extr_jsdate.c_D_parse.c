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
 int /*<<< orphan*/  js_pushnumber (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  js_tostring (int /*<<< orphan*/ *,int) ; 
 double parseDateTime (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void D_parse(js_State *J)
{
	double t = parseDateTime(js_tostring(J, 1));
	js_pushnumber(J, t);
}