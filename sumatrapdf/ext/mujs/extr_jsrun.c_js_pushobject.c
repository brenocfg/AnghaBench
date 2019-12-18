#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
typedef  int /*<<< orphan*/  js_Object ;
struct TYPE_3__ {int /*<<< orphan*/ * object; } ;
struct TYPE_4__ {TYPE_1__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSTACK (int) ; 
 int /*<<< orphan*/  JS_TOBJECT ; 
 TYPE_2__* STACK ; 
 size_t TOP ; 

void js_pushobject(js_State *J, js_Object *v)
{
	CHECKSTACK(1);
	STACK[TOP].type = JS_TOBJECT;
	STACK[TOP].u.object = v;
	++TOP;
}