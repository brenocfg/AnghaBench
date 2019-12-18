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
 int /*<<< orphan*/  LocalTime (double) ; 
 int /*<<< orphan*/  fmtdate (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 double js_todate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Dp_toDateString(js_State *J)
{
	char buf[64];
	double t = js_todate(J, 0);
	js_pushstring(J, fmtdate(buf, LocalTime(t)));
}