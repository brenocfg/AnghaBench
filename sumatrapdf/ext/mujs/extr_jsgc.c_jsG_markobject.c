#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_10__ {TYPE_7__* function; TYPE_8__* scope; } ;
struct TYPE_9__ {TYPE_4__* target; } ;
struct TYPE_11__ {TYPE_2__ f; TYPE_1__ iter; } ;
struct TYPE_12__ {int gcmark; scalar_t__ type; TYPE_3__ u; struct TYPE_12__* prototype; TYPE_5__* properties; } ;
typedef  TYPE_4__ js_Object ;
struct TYPE_15__ {int gcmark; } ;
struct TYPE_14__ {int gcmark; } ;
struct TYPE_13__ {scalar_t__ level; } ;

/* Variables and functions */
 scalar_t__ JS_CFUNCTION ; 
 scalar_t__ JS_CITERATOR ; 
 scalar_t__ JS_CSCRIPT ; 
 int /*<<< orphan*/  jsG_markenvironment (int /*<<< orphan*/ *,int,TYPE_8__*) ; 
 int /*<<< orphan*/  jsG_markfunction (int /*<<< orphan*/ *,int,TYPE_7__*) ; 
 int /*<<< orphan*/  jsG_markproperty (int /*<<< orphan*/ *,int,TYPE_5__*) ; 

__attribute__((used)) static void jsG_markobject(js_State *J, int mark, js_Object *obj)
{
	obj->gcmark = mark;
	if (obj->properties->level)
		jsG_markproperty(J, mark, obj->properties);
	if (obj->prototype && obj->prototype->gcmark != mark)
		jsG_markobject(J, mark, obj->prototype);
	if (obj->type == JS_CITERATOR) {
		jsG_markobject(J, mark, obj->u.iter.target);
	}
	if (obj->type == JS_CFUNCTION || obj->type == JS_CSCRIPT) {
		if (obj->u.f.scope && obj->u.f.scope->gcmark != mark)
			jsG_markenvironment(J, mark, obj->u.f.scope);
		if (obj->u.f.function && obj->u.f.function->gcmark != mark)
			jsG_markfunction(J, mark, obj->u.f.function);
	}
}