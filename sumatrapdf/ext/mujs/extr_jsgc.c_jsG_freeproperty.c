#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_4__ {struct TYPE_4__* right; scalar_t__ level; struct TYPE_4__* left; } ;
typedef  TYPE_1__ js_Property ;

/* Variables and functions */
 int /*<<< orphan*/  js_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void jsG_freeproperty(js_State *J, js_Property *node)
{
	if (node->left->level) jsG_freeproperty(J, node->left);
	if (node->right->level) jsG_freeproperty(J, node->right);
	js_free(J, node);
}