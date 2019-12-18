#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ number; scalar_t__ boolean; scalar_t__ object; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_1__ u; } ;
typedef  TYPE_2__ js_Value ;
typedef  int /*<<< orphan*/  js_State ;

/* Variables and functions */
 scalar_t__ JSV_ISSTRING (TYPE_2__*) ; 
 int /*<<< orphan*/  JSV_TOSTRING (TYPE_2__*) ; 
 int /*<<< orphan*/  JS_HNONE ; 
 scalar_t__ JS_TBOOLEAN ; 
 scalar_t__ JS_TNULL ; 
 scalar_t__ JS_TNUMBER ; 
 scalar_t__ JS_TOBJECT ; 
 scalar_t__ JS_TUNDEFINED ; 
 scalar_t__ jsV_tonumber (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  jsV_toprimitive (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* js_tovalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int js_equal(js_State *J)
{
	js_Value *x = js_tovalue(J, -2);
	js_Value *y = js_tovalue(J, -1);

retry:
	if (JSV_ISSTRING(x) && JSV_ISSTRING(y))
		return !strcmp(JSV_TOSTRING(x), JSV_TOSTRING(y));
	if (x->type == y->type) {
		if (x->type == JS_TUNDEFINED) return 1;
		if (x->type == JS_TNULL) return 1;
		if (x->type == JS_TNUMBER) return x->u.number == y->u.number;
		if (x->type == JS_TBOOLEAN) return x->u.boolean == y->u.boolean;
		if (x->type == JS_TOBJECT) return x->u.object == y->u.object;
		return 0;
	}

	if (x->type == JS_TNULL && y->type == JS_TUNDEFINED) return 1;
	if (x->type == JS_TUNDEFINED && y->type == JS_TNULL) return 1;

	if (x->type == JS_TNUMBER && JSV_ISSTRING(y))
		return x->u.number == jsV_tonumber(J, y);
	if (JSV_ISSTRING(x) && y->type == JS_TNUMBER)
		return jsV_tonumber(J, x) == y->u.number;

	if (x->type == JS_TBOOLEAN) {
		x->type = JS_TNUMBER;
		x->u.number = x->u.boolean;
		goto retry;
	}
	if (y->type == JS_TBOOLEAN) {
		y->type = JS_TNUMBER;
		y->u.number = y->u.boolean;
		goto retry;
	}
	if ((JSV_ISSTRING(x) || x->type == JS_TNUMBER) && y->type == JS_TOBJECT) {
		jsV_toprimitive(J, y, JS_HNONE);
		goto retry;
	}
	if (x->type == JS_TOBJECT && (JSV_ISSTRING(y) || y->type == JS_TNUMBER)) {
		jsV_toprimitive(J, x, JS_HNONE);
		goto retry;
	}

	return 0;
}