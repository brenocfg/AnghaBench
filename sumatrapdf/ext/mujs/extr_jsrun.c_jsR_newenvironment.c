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
struct TYPE_8__ {int /*<<< orphan*/  gccounter; TYPE_2__* gcenv; } ;
typedef  TYPE_1__ js_State ;
typedef  int /*<<< orphan*/  js_Object ;
struct TYPE_9__ {int /*<<< orphan*/ * variables; struct TYPE_9__* outer; struct TYPE_9__* gcnext; scalar_t__ gcmark; } ;
typedef  TYPE_2__ js_Environment ;

/* Variables and functions */
 TYPE_2__* js_malloc (TYPE_1__*,int) ; 

js_Environment *jsR_newenvironment(js_State *J, js_Object *vars, js_Environment *outer)
{
	js_Environment *E = js_malloc(J, sizeof *E);
	E->gcmark = 0;
	E->gcnext = J->gcenv;
	J->gcenv = E;
	++J->gccounter;

	E->outer = outer;
	E->variables = vars;
	return E;
}