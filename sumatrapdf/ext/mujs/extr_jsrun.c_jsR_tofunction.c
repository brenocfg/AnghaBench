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
struct TYPE_6__ {TYPE_3__* object; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_1__ u; } ;
typedef  TYPE_2__ js_Value ;
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_8__ {scalar_t__ type; } ;
typedef  TYPE_3__ js_Object ;

/* Variables and functions */
 scalar_t__ JS_CCFUNCTION ; 
 scalar_t__ JS_CFUNCTION ; 
 scalar_t__ JS_TNULL ; 
 scalar_t__ JS_TOBJECT ; 
 scalar_t__ JS_TUNDEFINED ; 
 int /*<<< orphan*/  js_typeerror (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* stackidx (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static js_Object *jsR_tofunction(js_State *J, int idx)
{
	js_Value *v = stackidx(J, idx);
	if (v->type == JS_TUNDEFINED || v->type == JS_TNULL)
		return NULL;
	if (v->type == JS_TOBJECT)
		if (v->u.object->type == JS_CFUNCTION || v->u.object->type == JS_CCFUNCTION)
			return v->u.object;
	js_typeerror(J, "not a function");
}