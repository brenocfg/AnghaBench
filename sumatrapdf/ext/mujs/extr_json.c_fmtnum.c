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
typedef  int /*<<< orphan*/  js_Buffer ;

/* Variables and functions */
 scalar_t__ isinf (double) ; 
 scalar_t__ isnan (double) ; 
 char* jsV_numbertostring (int /*<<< orphan*/ *,char*,double) ; 
 int /*<<< orphan*/  js_puts (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char*) ; 

__attribute__((used)) static void fmtnum(js_State *J, js_Buffer **sb, double n)
{
	if (isnan(n)) js_puts(J, sb, "null");
	else if (isinf(n)) js_puts(J, sb, "null");
	else if (n == 0) js_puts(J, sb, "0");
	else {
		char buf[40];
		js_puts(J, sb, jsV_numbertostring(J, buf, n));
	}
}