#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_4__ {int /*<<< orphan*/  properties; } ;
typedef  TYPE_1__ js_Object ;

/* Variables and functions */
 int /*<<< orphan*/  delete (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 

void jsV_delproperty(js_State *J, js_Object *obj, const char *name)
{
	obj->properties = delete(J, obj, obj->properties, name);
}