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
typedef  int /*<<< orphan*/  js_Object ;

/* Variables and functions */
 int /*<<< orphan*/  JS_COBJECT ; 
 int /*<<< orphan*/  jsV_newobject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ js_isobject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushobject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * js_toobject (int /*<<< orphan*/ *,int) ; 

void js_newobjectx(js_State *J)
{
	js_Object *prototype = NULL;
	if (js_isobject(J, -1))
		prototype = js_toobject(J, -1);
	js_pop(J, 1);
	js_pushobject(J, jsV_newobject(J, JS_COBJECT, prototype));
}