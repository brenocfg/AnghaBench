#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_7__* object; TYPE_2__* memstr; } ;
struct TYPE_10__ {scalar_t__ type; TYPE_1__ u; } ;
typedef  TYPE_3__ js_Value ;
struct TYPE_11__ {int top; TYPE_3__* stack; } ;
typedef  TYPE_4__ js_State ;
struct TYPE_12__ {int gcmark; } ;
struct TYPE_9__ {int gcmark; } ;

/* Variables and functions */
 scalar_t__ JS_TMEMSTR ; 
 scalar_t__ JS_TOBJECT ; 
 int /*<<< orphan*/  jsG_markobject (TYPE_4__*,int,TYPE_7__*) ; 

__attribute__((used)) static void jsG_markstack(js_State *J, int mark)
{
	js_Value *v = J->stack;
	int n = J->top;
	while (n--) {
		if (v->type == JS_TMEMSTR && v->u.memstr->gcmark != mark)
			v->u.memstr->gcmark = mark;
		if (v->type == JS_TOBJECT && v->u.object->gcmark != mark)
			jsG_markobject(J, mark, v->u.object);
		++v;
	}
}