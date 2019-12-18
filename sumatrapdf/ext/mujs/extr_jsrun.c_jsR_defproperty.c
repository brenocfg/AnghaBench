#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_Value ;
struct TYPE_20__ {scalar_t__ strict; } ;
typedef  TYPE_4__ js_State ;
struct TYPE_21__ {int atts; TYPE_6__* setter; TYPE_6__* getter; int /*<<< orphan*/  value; } ;
typedef  TYPE_5__ js_Property ;
struct TYPE_18__ {int /*<<< orphan*/  data; scalar_t__ (* put ) (TYPE_4__*,int /*<<< orphan*/ ,char const*) ;} ;
struct TYPE_17__ {int length; } ;
struct TYPE_19__ {TYPE_2__ user; TYPE_1__ s; } ;
struct TYPE_22__ {scalar_t__ type; TYPE_3__ u; } ;
typedef  TYPE_6__ js_Object ;

/* Variables and functions */
 scalar_t__ JS_CARRAY ; 
 scalar_t__ JS_CREGEXP ; 
 scalar_t__ JS_CSTRING ; 
 scalar_t__ JS_CUSERDATA ; 
 int JS_DONTCONF ; 
 int JS_READONLY ; 
 TYPE_5__* jsV_setproperty (TYPE_4__*,TYPE_6__*,char const*) ; 
 scalar_t__ js_isarrayindex (TYPE_4__*,char const*,int*) ; 
 int /*<<< orphan*/  js_typeerror (TYPE_4__*,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ stub1 (TYPE_4__*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void jsR_defproperty(js_State *J, js_Object *obj, const char *name,
	int atts, js_Value *value, js_Object *getter, js_Object *setter)
{
	js_Property *ref;
	int k;

	if (obj->type == JS_CARRAY) {
		if (!strcmp(name, "length"))
			goto readonly;
	}

	else if (obj->type == JS_CSTRING) {
		if (!strcmp(name, "length"))
			goto readonly;
		if (js_isarrayindex(J, name, &k))
			if (k >= 0 && k < obj->u.s.length)
				goto readonly;
	}

	else if (obj->type == JS_CREGEXP) {
		if (!strcmp(name, "source")) goto readonly;
		if (!strcmp(name, "global")) goto readonly;
		if (!strcmp(name, "ignoreCase")) goto readonly;
		if (!strcmp(name, "multiline")) goto readonly;
		if (!strcmp(name, "lastIndex")) goto readonly;
	}

	else if (obj->type == JS_CUSERDATA) {
		if (obj->u.user.put && obj->u.user.put(J, obj->u.user.data, name))
			return;
	}

	ref = jsV_setproperty(J, obj, name);
	if (ref) {
		if (value) {
			if (!(ref->atts & JS_READONLY))
				ref->value = *value;
			else if (J->strict)
				js_typeerror(J, "'%s' is read-only", name);
		}
		if (getter) {
			if (!(ref->atts & JS_DONTCONF))
				ref->getter = getter;
			else if (J->strict)
				js_typeerror(J, "'%s' is non-configurable", name);
		}
		if (setter) {
			if (!(ref->atts & JS_DONTCONF))
				ref->setter = setter;
			else if (J->strict)
				js_typeerror(J, "'%s' is non-configurable", name);
		}
		ref->atts |= atts;
	}

	return;

readonly:
	if (J->strict)
		js_typeerror(J, "'%s' is read-only or non-configurable", name);
}