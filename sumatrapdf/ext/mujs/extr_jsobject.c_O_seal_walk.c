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
struct TYPE_3__ {struct TYPE_3__* right; scalar_t__ level; int /*<<< orphan*/  atts; struct TYPE_3__* left; } ;
typedef  TYPE_1__ js_Property ;

/* Variables and functions */
 int /*<<< orphan*/  JS_DONTCONF ; 

__attribute__((used)) static void O_seal_walk(js_State *J, js_Property *ref)
{
	if (ref->left->level)
		O_seal_walk(J, ref->left);
	ref->atts |= JS_DONTCONF;
	if (ref->right->level)
		O_seal_walk(J, ref->right);
}