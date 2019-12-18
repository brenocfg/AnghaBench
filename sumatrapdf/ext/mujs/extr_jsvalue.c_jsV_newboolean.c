#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  Boolean_prototype; } ;
typedef  TYPE_2__ js_State ;
struct TYPE_8__ {int boolean; } ;
struct TYPE_10__ {TYPE_1__ u; } ;
typedef  TYPE_3__ js_Object ;

/* Variables and functions */
 int /*<<< orphan*/  JS_CBOOLEAN ; 
 TYPE_3__* jsV_newobject (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static js_Object *jsV_newboolean(js_State *J, int v)
{
	js_Object *obj = jsV_newobject(J, JS_CBOOLEAN, J->Boolean_prototype);
	obj->u.boolean = v;
	return obj;
}