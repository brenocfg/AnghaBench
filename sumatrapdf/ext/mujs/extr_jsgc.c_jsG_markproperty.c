#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_8__ {TYPE_6__* object; TYPE_1__* memstr; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_2__ u; } ;
struct TYPE_10__ {TYPE_6__* setter; TYPE_6__* getter; TYPE_3__ value; struct TYPE_10__* right; scalar_t__ level; struct TYPE_10__* left; } ;
typedef  TYPE_4__ js_Property ;
struct TYPE_11__ {int gcmark; } ;
struct TYPE_7__ {int gcmark; } ;

/* Variables and functions */
 scalar_t__ JS_TMEMSTR ; 
 scalar_t__ JS_TOBJECT ; 
 int /*<<< orphan*/  jsG_markobject (int /*<<< orphan*/ *,int,TYPE_6__*) ; 

__attribute__((used)) static void jsG_markproperty(js_State *J, int mark, js_Property *node)
{
	if (node->left->level) jsG_markproperty(J, mark, node->left);
	if (node->right->level) jsG_markproperty(J, mark, node->right);

	if (node->value.type == JS_TMEMSTR && node->value.u.memstr->gcmark != mark)
		node->value.u.memstr->gcmark = mark;
	if (node->value.type == JS_TOBJECT && node->value.u.object->gcmark != mark)
		jsG_markobject(J, mark, node->value.u.object);
	if (node->getter && node->getter->gcmark != mark)
		jsG_markobject(J, mark, node->getter);
	if (node->setter && node->setter->gcmark != mark)
		jsG_markobject(J, mark, node->setter);
}