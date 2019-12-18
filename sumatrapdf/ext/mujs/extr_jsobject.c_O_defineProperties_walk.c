#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_3__ {int atts; struct TYPE_3__* right; scalar_t__ level; int /*<<< orphan*/  name; int /*<<< orphan*/  value; struct TYPE_3__* left; } ;
typedef  TYPE_1__ js_Property ;

/* Variables and functions */
 int JS_DONTENUM ; 
 int /*<<< orphan*/  ToPropertyDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_toobject (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void O_defineProperties_walk(js_State *J, js_Property *ref)
{
	if (ref->left->level)
		O_defineProperties_walk(J, ref->left);
	if (!(ref->atts & JS_DONTENUM)) {
		js_pushvalue(J, ref->value);
		ToPropertyDescriptor(J, js_toobject(J, 1), ref->name, js_toobject(J, -1));
		js_pop(J, 1);
	}
	if (ref->right->level)
		O_defineProperties_walk(J, ref->right);
}