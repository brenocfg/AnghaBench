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
 int /*<<< orphan*/  js_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_loadeval (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_rot2pop1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_tostring (int /*<<< orphan*/ *,int) ; 

void js_eval(js_State *J)
{
	if (!js_isstring(J, -1))
		return;
	js_loadeval(J, "(eval)", js_tostring(J, -1));
	js_rot2pop1(J);
	js_copy(J, 0); /* copy 'this' */
	js_call(J, 0);
}