#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  gccounter; TYPE_2__* gcobj; } ;
typedef  TYPE_1__ js_State ;
struct TYPE_10__ {int type; int extensible; struct TYPE_10__* prototype; int /*<<< orphan*/ * properties; struct TYPE_10__* gcnext; scalar_t__ gcmark; } ;
typedef  TYPE_2__ js_Object ;
typedef  enum js_Class { ____Placeholder_js_Class } js_Class ;

/* Variables and functions */
 TYPE_2__* js_malloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sentinel ; 

js_Object *jsV_newobject(js_State *J, enum js_Class type, js_Object *prototype)
{
	js_Object *obj = js_malloc(J, sizeof *obj);
	memset(obj, 0, sizeof *obj);
	obj->gcmark = 0;
	obj->gcnext = J->gcobj;
	J->gcobj = obj;
	++J->gccounter;

	obj->type = type;
	obj->properties = &sentinel;
	obj->prototype = prototype;
	obj->extensible = 1;
	return obj;
}