#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* right; struct TYPE_5__* left; } ;
typedef  TYPE_1__ js_StringNode ;
typedef  int /*<<< orphan*/  js_State ;

/* Variables and functions */
 TYPE_1__ jsS_sentinel ; 
 int /*<<< orphan*/  js_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void jsS_freestringnode(js_State *J, js_StringNode *node)
{
	if (node->left != &jsS_sentinel) jsS_freestringnode(J, node->left);
	if (node->right != &jsS_sentinel) jsS_freestringnode(J, node->right);
	js_free(J, node);
}