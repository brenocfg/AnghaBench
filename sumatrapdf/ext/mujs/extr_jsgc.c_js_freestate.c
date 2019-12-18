#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {struct TYPE_20__* gcnext; } ;
typedef  TYPE_2__ js_String ;
struct TYPE_19__ {TYPE_2__* text; } ;
struct TYPE_21__ {int /*<<< orphan*/  actx; int /*<<< orphan*/  (* alloc ) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ;struct TYPE_21__* stack; TYPE_1__ lexbuf; TYPE_2__* gcstr; TYPE_4__* gcobj; TYPE_5__* gcfun; TYPE_6__* gcenv; } ;
typedef  TYPE_3__ js_State ;
struct TYPE_22__ {struct TYPE_22__* gcnext; } ;
typedef  TYPE_4__ js_Object ;
struct TYPE_23__ {struct TYPE_23__* gcnext; } ;
typedef  TYPE_5__ js_Function ;
struct TYPE_24__ {struct TYPE_24__* gcnext; } ;
typedef  TYPE_6__ js_Environment ;

/* Variables and functions */
 int /*<<< orphan*/  jsG_freeenvironment (TYPE_3__*,TYPE_6__*) ; 
 int /*<<< orphan*/  jsG_freefunction (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  jsG_freeobject (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  jsS_freestrings (TYPE_3__*) ; 
 int /*<<< orphan*/  js_free (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 

void js_freestate(js_State *J)
{
	js_Function *fun, *nextfun;
	js_Object *obj, *nextobj;
	js_Environment *env, *nextenv;
	js_String *str, *nextstr;

	if (!J)
		return;

	for (env = J->gcenv; env; env = nextenv)
		nextenv = env->gcnext, jsG_freeenvironment(J, env);
	for (fun = J->gcfun; fun; fun = nextfun)
		nextfun = fun->gcnext, jsG_freefunction(J, fun);
	for (obj = J->gcobj; obj; obj = nextobj)
		nextobj = obj->gcnext, jsG_freeobject(J, obj);
	for (str = J->gcstr; str; str = nextstr)
		nextstr = str->gcnext, js_free(J, str);

	jsS_freestrings(J);

	js_free(J, J->lexbuf.text);
	J->alloc(J->actx, J->stack, 0);
	J->alloc(J->actx, J, 0);
}