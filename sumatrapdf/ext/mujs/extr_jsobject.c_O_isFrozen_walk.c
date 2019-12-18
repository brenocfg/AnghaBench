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
struct TYPE_3__ {int atts; struct TYPE_3__* right; scalar_t__ level; struct TYPE_3__* left; } ;
typedef  TYPE_1__ js_Property ;

/* Variables and functions */
 int JS_DONTCONF ; 
 int JS_READONLY ; 

__attribute__((used)) static int O_isFrozen_walk(js_State *J, js_Property *ref)
{
	if (ref->left->level)
		if (!O_isFrozen_walk(J, ref->left))
			return 0;
	if (!(ref->atts & JS_READONLY))
		return 0;
	if (!(ref->atts & JS_DONTCONF))
		return 0;
	if (ref->right->level)
		if (!O_isFrozen_walk(J, ref->right))
			return 0;
	return 1;
}