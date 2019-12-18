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
 int /*<<< orphan*/  js_replace (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_repr (int /*<<< orphan*/ *,int) ; 
 char const* js_tostring (int /*<<< orphan*/ *,int) ; 

const char *js_torepr(js_State *J, int idx)
{
	js_repr(J, idx);
	js_replace(J, idx < 0 ? idx-1 : idx);
	return js_tostring(J, idx);
}