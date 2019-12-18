#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_6__ {int /*<<< orphan*/ * scope; int /*<<< orphan*/ * function; } ;
struct TYPE_7__ {TYPE_1__ f; } ;
struct TYPE_8__ {TYPE_2__ u; } ;
typedef  TYPE_3__ js_Object ;
typedef  int /*<<< orphan*/  js_Function ;
typedef  int /*<<< orphan*/  js_Environment ;

/* Variables and functions */
 int /*<<< orphan*/  JS_CSCRIPT ; 
 TYPE_3__* jsV_newobject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pushobject (int /*<<< orphan*/ *,TYPE_3__*) ; 

void js_newscript(js_State *J, js_Function *fun, js_Environment *scope)
{
	js_Object *obj = jsV_newobject(J, JS_CSCRIPT, NULL);
	obj->u.f.function = fun;
	obj->u.f.scope = scope;
	js_pushobject(J, obj);
}