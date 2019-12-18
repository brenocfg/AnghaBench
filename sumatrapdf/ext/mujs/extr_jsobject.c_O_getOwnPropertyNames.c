#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_6__ {int length; } ;
struct TYPE_7__ {TYPE_1__ s; } ;
struct TYPE_8__ {scalar_t__ type; TYPE_2__ u; TYPE_5__* properties; } ;
typedef  TYPE_3__ js_Object ;
struct TYPE_9__ {scalar_t__ level; } ;

/* Variables and functions */
 scalar_t__ JS_CARRAY ; 
 scalar_t__ JS_CREGEXP ; 
 scalar_t__ JS_CSTRING ; 
 int O_getOwnPropertyNames_walk (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_isobject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_newarray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  js_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_setindex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* js_toobject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_typeerror (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void O_getOwnPropertyNames(js_State *J)
{
	js_Object *obj;
	int k;
	int i;

	if (!js_isobject(J, 1))
		js_typeerror(J, "not an object");
	obj = js_toobject(J, 1);

	js_newarray(J);

	if (obj->properties->level)
		i = O_getOwnPropertyNames_walk(J, obj->properties, 0);
	else
		i = 0;

	if (obj->type == JS_CARRAY) {
		js_pushliteral(J, "length");
		js_setindex(J, -2, i++);
	}

	if (obj->type == JS_CSTRING) {
		js_pushliteral(J, "length");
		js_setindex(J, -2, i++);
		for (k = 0; k < obj->u.s.length; ++k) {
			js_pushnumber(J, k);
			js_setindex(J, -2, i++);
		}
	}

	if (obj->type == JS_CREGEXP) {
		js_pushliteral(J, "source");
		js_setindex(J, -2, i++);
		js_pushliteral(J, "global");
		js_setindex(J, -2, i++);
		js_pushliteral(J, "ignoreCase");
		js_setindex(J, -2, i++);
		js_pushliteral(J, "multiline");
		js_setindex(J, -2, i++);
		js_pushliteral(J, "lastIndex");
		js_setindex(J, -2, i++);
	}
}