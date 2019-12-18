#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_4__ {TYPE_2__* properties; } ;
typedef  TYPE_1__ js_Object ;
struct TYPE_5__ {scalar_t__ level; } ;

/* Variables and functions */
 int /*<<< orphan*/  js_dumpproperty (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ minify ; 
 int /*<<< orphan*/  printf (char*) ; 

void js_dumpobject(js_State *J, js_Object *obj)
{
	minify = 0;
	printf("{\n");
	if (obj->properties->level)
		js_dumpproperty(J, obj->properties);
	printf("}\n");
}