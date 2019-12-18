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
 char* jsV_numbertostring (int /*<<< orphan*/ *,char*,double) ; 
 int /*<<< orphan*/  js_puts (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char*) ; 
 scalar_t__ signbit (double) ; 

__attribute__((used)) static void reprnum(js_State *J, js_Buffer **sb, double n)
{
	char buf[40];
	if (n == 0 && signbit(n))
		js_puts(J, sb, "-0");
	else
		js_puts(J, sb, jsV_numbertostring(J, buf, n));
}