#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_6__ {int atts; } ;
typedef  TYPE_1__ js_Property ;
struct TYPE_7__ {struct TYPE_7__* prototype; int /*<<< orphan*/  properties; } ;
typedef  TYPE_2__ js_Object ;

/* Variables and functions */
 int JS_DONTENUM ; 
 TYPE_1__* lookup (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static js_Property *jsV_getenumproperty(js_State *J, js_Object *obj, const char *name)
{
	do {
		js_Property *ref = lookup(obj->properties, name);
		if (ref && !(ref->atts & JS_DONTENUM))
			return ref;
		obj = obj->prototype;
	} while (obj);
	return NULL;
}