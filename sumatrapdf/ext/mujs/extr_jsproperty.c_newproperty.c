#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_8__ {scalar_t__ number; } ;
struct TYPE_9__ {TYPE_1__ u; int /*<<< orphan*/  type; } ;
struct TYPE_10__ {int level; int /*<<< orphan*/ * setter; int /*<<< orphan*/ * getter; TYPE_2__ value; scalar_t__ atts; int /*<<< orphan*/ * right; int /*<<< orphan*/ * left; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ js_Property ;
struct TYPE_11__ {int /*<<< orphan*/  count; } ;
typedef  TYPE_4__ js_Object ;

/* Variables and functions */
 int /*<<< orphan*/  JS_TUNDEFINED ; 
 int /*<<< orphan*/  js_intern (int /*<<< orphan*/ *,char const*) ; 
 TYPE_3__* js_malloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sentinel ; 

__attribute__((used)) static js_Property *newproperty(js_State *J, js_Object *obj, const char *name)
{
	js_Property *node = js_malloc(J, sizeof *node);
	node->name = js_intern(J, name);
	node->left = node->right = &sentinel;
	node->level = 1;
	node->atts = 0;
	node->value.type = JS_TUNDEFINED;
	node->value.u.number = 0;
	node->getter = NULL;
	node->setter = NULL;
	++obj->count;
	return node;
}