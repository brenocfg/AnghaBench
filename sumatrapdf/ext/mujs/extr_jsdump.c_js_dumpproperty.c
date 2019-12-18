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
struct TYPE_3__ {char* name; struct TYPE_3__* right; scalar_t__ level; int /*<<< orphan*/  value; struct TYPE_3__* left; } ;
typedef  TYPE_1__ js_Property ;

/* Variables and functions */
 int /*<<< orphan*/  js_dumpvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ minify ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void js_dumpproperty(js_State *J, js_Property *node)
{
	minify = 0;
	if (node->left->level)
		js_dumpproperty(J, node->left);
	printf("\t%s: ", node->name);
	js_dumpvalue(J, node->value);
	printf(",\n");
	if (node->right->level)
		js_dumpproperty(J, node->right);
}