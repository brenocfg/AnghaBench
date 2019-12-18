#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_8__ {char* name; int level; struct TYPE_8__* right; struct TYPE_8__* left; int /*<<< orphan*/  value; int /*<<< orphan*/  atts; } ;
typedef  TYPE_1__ js_Property ;
typedef  int /*<<< orphan*/  js_Object ;

/* Variables and functions */
 int /*<<< orphan*/  freeproperty (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__ sentinel ; 
 void* skew (TYPE_1__*) ; 
 void* split (TYPE_1__*) ; 
 int strcmp (char const*,char*) ; 

__attribute__((used)) static js_Property *delete(js_State *J, js_Object *obj, js_Property *node, const char *name)
{
	js_Property *temp, *succ;

	if (node != &sentinel) {
		int c = strcmp(name, node->name);
		if (c < 0) {
			node->left = delete(J, obj, node->left, name);
		} else if (c > 0) {
			node->right = delete(J, obj, node->right, name);
		} else {
			if (node->left == &sentinel) {
				temp = node;
				node = node->right;
				freeproperty(J, obj, temp);
			} else if (node->right == &sentinel) {
				temp = node;
				node = node->left;
				freeproperty(J, obj, temp);
			} else {
				succ = node->right;
				while (succ->left != &sentinel)
					succ = succ->left;
				node->name = succ->name;
				node->atts = succ->atts;
				node->value = succ->value;
				node->right = delete(J, obj, node->right, succ->name);
			}
		}

		if (node->left->level < node->level - 1 ||
			node->right->level < node->level - 1)
		{
			if (node->right->level > --node->level)
				node->right->level = node->level;
			node = skew(node);
			node->right = skew(node->right);
			node->right->right = skew(node->right->right);
			node = split(node);
			node->right = split(node->right);
		}
	}
	return node;
}