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
typedef  int /*<<< orphan*/  js_Property ;
struct TYPE_3__ {struct TYPE_3__* prototype; int /*<<< orphan*/  properties; } ;
typedef  TYPE_1__ js_Object ;

/* Variables and functions */
 int /*<<< orphan*/ * lookup (int /*<<< orphan*/ ,char const*) ; 

js_Property *jsV_getpropertyx(js_State *J, js_Object *obj, const char *name, int *own)
{
	*own = 1;
	do {
		js_Property *ref = lookup(obj->properties, name);
		if (ref)
			return ref;
		obj = obj->prototype;
		*own = 0;
	} while (obj);
	return NULL;
}