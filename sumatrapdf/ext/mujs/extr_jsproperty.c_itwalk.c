#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_8__ {int atts; struct TYPE_8__* left; int /*<<< orphan*/  name; struct TYPE_8__* right; } ;
typedef  TYPE_1__ js_Property ;
typedef  int /*<<< orphan*/  js_Object ;
struct TYPE_9__ {struct TYPE_9__* next; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ js_Iterator ;

/* Variables and functions */
 int JS_DONTENUM ; 
 int /*<<< orphan*/  jsV_getenumproperty (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* js_malloc (int /*<<< orphan*/ *,int) ; 
 TYPE_1__ sentinel ; 

__attribute__((used)) static js_Iterator *itwalk(js_State *J, js_Iterator *iter, js_Property *prop, js_Object *seen)
{
	if (prop->right != &sentinel)
		iter = itwalk(J, iter, prop->right, seen);
	if (!(prop->atts & JS_DONTENUM)) {
		if (!seen || !jsV_getenumproperty(J, seen, prop->name)) {
			js_Iterator *head = js_malloc(J, sizeof *head);
			head->name = prop->name;
			head->next = iter;
			iter = head;
		}
	}
	if (prop->left != &sentinel)
		iter = itwalk(J, iter, prop->left, seen);
	return iter;
}