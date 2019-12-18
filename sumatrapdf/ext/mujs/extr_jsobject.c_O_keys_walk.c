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
struct TYPE_3__ {int atts; struct TYPE_3__* right; scalar_t__ level; int /*<<< orphan*/  name; struct TYPE_3__* left; } ;
typedef  TYPE_1__ js_Property ;

/* Variables and functions */
 int JS_DONTENUM ; 
 int /*<<< orphan*/  js_pushliteral (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_setindex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int O_keys_walk(js_State *J, js_Property *ref, int i)
{
	if (ref->left->level)
		i = O_keys_walk(J, ref->left, i);
	if (!(ref->atts & JS_DONTENUM)) {
		js_pushliteral(J, ref->name);
		js_setindex(J, -2, i++);
	}
	if (ref->right->level)
		i = O_keys_walk(J, ref->right, i);
	return i;
}