#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {TYPE_4__* Object_prototype; int /*<<< orphan*/  tracetop; } ;
typedef  TYPE_3__ js_State ;
struct TYPE_24__ {scalar_t__ constructor; int /*<<< orphan*/  length; int /*<<< orphan*/  name; } ;
struct TYPE_25__ {TYPE_1__ c; } ;
struct TYPE_27__ {scalar_t__ type; TYPE_2__ u; } ;
typedef  TYPE_4__ js_Object ;

/* Variables and functions */
 int BOT ; 
 scalar_t__ JS_CCFUNCTION ; 
 int /*<<< orphan*/  JS_COBJECT ; 
 int TOP ; 
 int /*<<< orphan*/  jsR_callcfunction (TYPE_3__*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  jsR_pushtrace (TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_4__* jsV_newobject (TYPE_3__*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  js_call (TYPE_3__*,int) ; 
 int /*<<< orphan*/  js_getproperty (TYPE_3__*,int,char*) ; 
 int /*<<< orphan*/  js_iscallable (TYPE_3__*,int) ; 
 scalar_t__ js_isobject (TYPE_3__*,int) ; 
 int /*<<< orphan*/  js_pop (TYPE_3__*,int) ; 
 int /*<<< orphan*/  js_pushnull (TYPE_3__*) ; 
 int /*<<< orphan*/  js_pushobject (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  js_rot (TYPE_3__*,int) ; 
 TYPE_4__* js_toobject (TYPE_3__*,int) ; 
 int /*<<< orphan*/  js_typeerror (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_typeof (TYPE_3__*,int) ; 

void js_construct(js_State *J, int n)
{
	js_Object *obj;
	js_Object *prototype;
	js_Object *newobj;

	if (!js_iscallable(J, -n-1))
		js_typeerror(J, "%s is not callable", js_typeof(J, -n-1));

	obj = js_toobject(J, -n-1);

	/* built-in constructors create their own objects, give them a 'null' this */
	if (obj->type == JS_CCFUNCTION && obj->u.c.constructor) {
		int savebot = BOT;
		js_pushnull(J);
		if (n > 0)
			js_rot(J, n + 1);
		BOT = TOP - n - 1;

		jsR_pushtrace(J, obj->u.c.name, "native", 0);
		jsR_callcfunction(J, n, obj->u.c.length, obj->u.c.constructor);
		--J->tracetop;

		BOT = savebot;
		return;
	}

	/* extract the function object's prototype property */
	js_getproperty(J, -n - 1, "prototype");
	if (js_isobject(J, -1))
		prototype = js_toobject(J, -1);
	else
		prototype = J->Object_prototype;
	js_pop(J, 1);

	/* create a new object with above prototype, and shift it into the 'this' slot */
	newobj = jsV_newobject(J, JS_COBJECT, prototype);
	js_pushobject(J, newobj);
	if (n > 0)
		js_rot(J, n + 1);

	/* call the function */
	js_call(J, n);

	/* if result is not an object, return the original object we created */
	if (!js_isobject(J, -1)) {
		js_pop(J, 1);
		js_pushobject(J, newobj);
	}
}