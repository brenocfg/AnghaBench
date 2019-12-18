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
struct TYPE_3__ {struct TYPE_3__* prototype; } ;
typedef  TYPE_1__ js_Object ;

/* Variables and functions */
 int /*<<< orphan*/  js_getproperty (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  js_iscallable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_isobject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* js_toobject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_typeerror (int /*<<< orphan*/ *,char*) ; 

int js_instanceof(js_State *J)
{
	js_Object *O, *V;

	if (!js_iscallable(J, -1))
		js_typeerror(J, "instanceof: invalid operand");

	if (!js_isobject(J, -2))
		return 0;

	js_getproperty(J, -1, "prototype");
	if (!js_isobject(J, -1))
		js_typeerror(J, "instanceof: 'prototype' property is not an object");
	O = js_toobject(J, -1);
	js_pop(J, 1);

	V = js_toobject(J, -2);
	while (V) {
		V = V->prototype;
		if (O == V)
			return 1;
	}

	return 0;
}