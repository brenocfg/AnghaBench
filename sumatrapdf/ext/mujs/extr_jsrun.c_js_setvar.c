#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  G; scalar_t__ strict; TYPE_3__* E; } ;
typedef  TYPE_1__ js_State ;
struct TYPE_16__ {int atts; int /*<<< orphan*/  value; scalar_t__ setter; } ;
typedef  TYPE_2__ js_Property ;
struct TYPE_17__ {struct TYPE_17__* outer; scalar_t__ variables; } ;
typedef  TYPE_3__ js_Environment ;

/* Variables and functions */
 int JS_READONLY ; 
 int /*<<< orphan*/  jsR_setproperty (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 
 TYPE_2__* jsV_getproperty (TYPE_1__*,scalar_t__,char const*) ; 
 int /*<<< orphan*/  js_call (TYPE_1__*,int) ; 
 int /*<<< orphan*/  js_copy (TYPE_1__*,int) ; 
 int /*<<< orphan*/  js_pop (TYPE_1__*,int) ; 
 int /*<<< orphan*/  js_pushobject (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  js_referenceerror (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  js_typeerror (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/ * stackidx (TYPE_1__*,int) ; 

__attribute__((used)) static void js_setvar(js_State *J, const char *name)
{
	js_Environment *E = J->E;
	do {
		js_Property *ref = jsV_getproperty(J, E->variables, name);
		if (ref) {
			if (ref->setter) {
				js_pushobject(J, ref->setter);
				js_pushobject(J, E->variables);
				js_copy(J, -3);
				js_call(J, 1);
				js_pop(J, 1);
				return;
			}
			if (!(ref->atts & JS_READONLY))
				ref->value = *stackidx(J, -1);
			else if (J->strict)
				js_typeerror(J, "'%s' is read-only", name);
			return;
		}
		E = E->outer;
	} while (E);
	if (J->strict)
		js_referenceerror(J, "assignment to undeclared variable '%s'", name);
	jsR_setproperty(J, J->G, name);
}