#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_3__ {int atts; int /*<<< orphan*/  setter; int /*<<< orphan*/  getter; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ js_Property ;
typedef  int /*<<< orphan*/  js_Object ;

/* Variables and functions */
 int JS_DONTCONF ; 
 int JS_DONTENUM ; 
 int JS_READONLY ; 
 TYPE_1__* jsV_getproperty (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_isobject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_newobject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushobject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pushundefined (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pushvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_setproperty (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/ * js_toobject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_typeerror (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void O_getOwnPropertyDescriptor(js_State *J)
{
	js_Object *obj;
	js_Property *ref;
	if (!js_isobject(J, 1))
		js_typeerror(J, "not an object");
	obj = js_toobject(J, 1);
	ref = jsV_getproperty(J, obj, js_tostring(J, 2));
	if (!ref)
		js_pushundefined(J);
	else {
		js_newobject(J);
		if (!ref->getter && !ref->setter) {
			js_pushvalue(J, ref->value);
			js_setproperty(J, -2, "value");
			js_pushboolean(J, !(ref->atts & JS_READONLY));
			js_setproperty(J, -2, "writable");
		} else {
			if (ref->getter)
				js_pushobject(J, ref->getter);
			else
				js_pushundefined(J);
			js_setproperty(J, -2, "get");
			if (ref->setter)
				js_pushobject(J, ref->setter);
			else
				js_pushundefined(J);
			js_setproperty(J, -2, "set");
		}
		js_pushboolean(J, !(ref->atts & JS_DONTENUM));
		js_setproperty(J, -2, "enumerable");
		js_pushboolean(J, !(ref->atts & JS_DONTCONF));
		js_setproperty(J, -2, "configurable");
	}
}