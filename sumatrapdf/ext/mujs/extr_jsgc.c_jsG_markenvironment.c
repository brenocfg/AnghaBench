#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_4__ {int gcmark; struct TYPE_4__* outer; TYPE_2__* variables; } ;
typedef  TYPE_1__ js_Environment ;
struct TYPE_5__ {int gcmark; } ;

/* Variables and functions */
 int /*<<< orphan*/  jsG_markobject (int /*<<< orphan*/ *,int,TYPE_2__*) ; 

__attribute__((used)) static void jsG_markenvironment(js_State *J, int mark, js_Environment *env)
{
	do {
		env->gcmark = mark;
		if (env->variables->gcmark != mark)
			jsG_markobject(J, mark, env->variables);
		env = env->outer;
	} while (env && env->gcmark != mark);
}