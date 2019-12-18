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
 double MakeDate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MakeDay (double,double,double) ; 
 int /*<<< orphan*/  MakeTime (double,double,double,double) ; 
 double TimeClip (double) ; 
 double js_optnumber (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  js_pushnumber (int /*<<< orphan*/ *,double) ; 
 double js_tonumber (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void D_UTC(js_State *J)
{
	double y, m, d, H, M, S, ms, t;
	y = js_tonumber(J, 1);
	if (y < 100) y += 1900;
	m = js_tonumber(J, 2);
	d = js_optnumber(J, 3, 1);
	H = js_optnumber(J, 4, 0);
	M = js_optnumber(J, 5, 0);
	S = js_optnumber(J, 6, 0);
	ms = js_optnumber(J, 7, 0);
	t = MakeDate(MakeDay(y, m, d), MakeTime(H, M, S, ms));
	t = TimeClip(t);
	js_pushnumber(J, t);
}