#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_11__ {struct TYPE_11__* right; struct TYPE_11__* left; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ js_Property ;
typedef  int /*<<< orphan*/  js_Object ;

/* Variables and functions */
 TYPE_1__* newproperty (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 TYPE_1__ sentinel ; 
 TYPE_1__* skew (TYPE_1__*) ; 
 TYPE_1__* split (TYPE_1__*) ; 
 int strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static js_Property *insert(js_State *J, js_Object *obj, js_Property *node, const char *name, js_Property **result)
{
	if (node != &sentinel) {
		int c = strcmp(name, node->name);
		if (c < 0)
			node->left = insert(J, obj, node->left, name, result);
		else if (c > 0)
			node->right = insert(J, obj, node->right, name, result);
		else
			return *result = node;
		node = skew(node);
		node = split(node);
		return node;
	}
	return *result = newproperty(J, obj, name);
}