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
 scalar_t__ BOT ; 
 scalar_t__ TOP ; 
 int /*<<< orphan*/  js_error (int /*<<< orphan*/ *,char*) ; 

void js_pop(js_State *J, int n)
{
	TOP -= n;
	if (TOP < BOT) {
		TOP = BOT;
		js_error(J, "stack underflow!");
	}
}