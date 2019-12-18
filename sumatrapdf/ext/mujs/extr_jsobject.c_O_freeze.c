#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_4__ {TYPE_3__* properties; scalar_t__ extensible; } ;
typedef  TYPE_1__ js_Object ;
struct TYPE_5__ {scalar_t__ level; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_freeze_walk (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  js_copy (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_isobject (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* js_toobject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_typeerror (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void O_freeze(js_State *J)
{
	js_Object *obj;

	if (!js_isobject(J, 1))
		js_typeerror(J, "not an object");

	obj = js_toobject(J, 1);
	obj->extensible = 0;

	if (obj->properties->level)
		O_freeze_walk(J, obj->properties);

	js_copy(J, 1);
}