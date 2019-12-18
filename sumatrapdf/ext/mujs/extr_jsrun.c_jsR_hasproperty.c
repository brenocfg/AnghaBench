#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_17__ {int /*<<< orphan*/  value; TYPE_7__* getter; } ;
typedef  TYPE_6__ js_Property ;
struct TYPE_15__ {int /*<<< orphan*/  data; scalar_t__ (* has ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ;} ;
struct TYPE_14__ {int flags; int last; int /*<<< orphan*/  source; } ;
struct TYPE_13__ {int length; int /*<<< orphan*/  string; } ;
struct TYPE_12__ {int length; } ;
struct TYPE_16__ {TYPE_4__ user; TYPE_3__ r; TYPE_2__ s; TYPE_1__ a; } ;
struct TYPE_18__ {scalar_t__ type; TYPE_5__ u; } ;
typedef  TYPE_7__ js_Object ;

/* Variables and functions */
 scalar_t__ JS_CARRAY ; 
 scalar_t__ JS_CREGEXP ; 
 scalar_t__ JS_CSTRING ; 
 scalar_t__ JS_CUSERDATA ; 
 int JS_REGEXP_G ; 
 int JS_REGEXP_I ; 
 int JS_REGEXP_M ; 
 TYPE_6__* jsV_getproperty (int /*<<< orphan*/ *,TYPE_7__*,char const*) ; 
 int /*<<< orphan*/  js_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ js_isarrayindex (int /*<<< orphan*/ *,char const*,int*) ; 
 int /*<<< orphan*/  js_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushliteral (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushobject (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  js_pushrune (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pushvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_runeat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int jsR_hasproperty(js_State *J, js_Object *obj, const char *name)
{
	js_Property *ref;
	int k;

	if (obj->type == JS_CARRAY) {
		if (!strcmp(name, "length")) {
			js_pushnumber(J, obj->u.a.length);
			return 1;
		}
	}

	else if (obj->type == JS_CSTRING) {
		if (!strcmp(name, "length")) {
			js_pushnumber(J, obj->u.s.length);
			return 1;
		}
		if (js_isarrayindex(J, name, &k)) {
			if (k >= 0 && k < obj->u.s.length) {
				js_pushrune(J, js_runeat(J, obj->u.s.string, k));
				return 1;
			}
		}
	}

	else if (obj->type == JS_CREGEXP) {
		if (!strcmp(name, "source")) {
			js_pushliteral(J, obj->u.r.source);
			return 1;
		}
		if (!strcmp(name, "global")) {
			js_pushboolean(J, obj->u.r.flags & JS_REGEXP_G);
			return 1;
		}
		if (!strcmp(name, "ignoreCase")) {
			js_pushboolean(J, obj->u.r.flags & JS_REGEXP_I);
			return 1;
		}
		if (!strcmp(name, "multiline")) {
			js_pushboolean(J, obj->u.r.flags & JS_REGEXP_M);
			return 1;
		}
		if (!strcmp(name, "lastIndex")) {
			js_pushnumber(J, obj->u.r.last);
			return 1;
		}
	}

	else if (obj->type == JS_CUSERDATA) {
		if (obj->u.user.has && obj->u.user.has(J, obj->u.user.data, name))
			return 1;
	}

	ref = jsV_getproperty(J, obj, name);
	if (ref) {
		if (ref->getter) {
			js_pushobject(J, ref->getter);
			js_pushobject(J, obj);
			js_call(J, 0);
		} else {
			js_pushvalue(J, ref->value);
		}
		return 1;
	}

	return 0;
}