#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int gcmark; struct TYPE_19__* gcnext; } ;
typedef  TYPE_1__ js_String ;
struct TYPE_20__ {int gcmark; int envtop; TYPE_1__* gcstr; TYPE_3__* gcobj; TYPE_4__* gcfun; TYPE_5__* gcenv; int /*<<< orphan*/ * envstack; int /*<<< orphan*/  GE; int /*<<< orphan*/  E; int /*<<< orphan*/  G; int /*<<< orphan*/  R; int /*<<< orphan*/  URIError_prototype; int /*<<< orphan*/  TypeError_prototype; int /*<<< orphan*/  SyntaxError_prototype; int /*<<< orphan*/  ReferenceError_prototype; int /*<<< orphan*/  RangeError_prototype; int /*<<< orphan*/  EvalError_prototype; int /*<<< orphan*/  Error_prototype; int /*<<< orphan*/  Date_prototype; int /*<<< orphan*/  RegExp_prototype; int /*<<< orphan*/  String_prototype; int /*<<< orphan*/  Number_prototype; int /*<<< orphan*/  Boolean_prototype; int /*<<< orphan*/  Function_prototype; int /*<<< orphan*/  Array_prototype; int /*<<< orphan*/  Object_prototype; scalar_t__ gccounter; scalar_t__ gcpause; } ;
typedef  TYPE_2__ js_State ;
struct TYPE_21__ {int gcmark; struct TYPE_21__* gcnext; } ;
typedef  TYPE_3__ js_Object ;
struct TYPE_22__ {int gcmark; struct TYPE_22__* gcnext; } ;
typedef  TYPE_4__ js_Function ;
struct TYPE_23__ {int gcmark; struct TYPE_23__* gcnext; } ;
typedef  TYPE_5__ js_Environment ;

/* Variables and functions */
 int /*<<< orphan*/  jsG_freeenvironment (TYPE_2__*,TYPE_5__*) ; 
 int /*<<< orphan*/  jsG_freefunction (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  jsG_freeobject (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  jsG_markenvironment (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsG_markobject (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsG_markstack (TYPE_2__*,int) ; 
 int /*<<< orphan*/  js_free (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  js_report (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,int,int,int,int,int) ; 

void js_gc(js_State *J, int report)
{
	js_Function *fun, *nextfun, **prevnextfun;
	js_Object *obj, *nextobj, **prevnextobj;
	js_String *str, *nextstr, **prevnextstr;
	js_Environment *env, *nextenv, **prevnextenv;
	int nenv = 0, nfun = 0, nobj = 0, nstr = 0;
	int genv = 0, gfun = 0, gobj = 0, gstr = 0;
	int mark;
	int i;

	if (J->gcpause) {
		if (report)
			js_report(J, "garbage collector is paused");
		return;
	}

	J->gccounter = 0;

	mark = J->gcmark = J->gcmark == 1 ? 2 : 1;

	jsG_markobject(J, mark, J->Object_prototype);
	jsG_markobject(J, mark, J->Array_prototype);
	jsG_markobject(J, mark, J->Function_prototype);
	jsG_markobject(J, mark, J->Boolean_prototype);
	jsG_markobject(J, mark, J->Number_prototype);
	jsG_markobject(J, mark, J->String_prototype);
	jsG_markobject(J, mark, J->RegExp_prototype);
	jsG_markobject(J, mark, J->Date_prototype);

	jsG_markobject(J, mark, J->Error_prototype);
	jsG_markobject(J, mark, J->EvalError_prototype);
	jsG_markobject(J, mark, J->RangeError_prototype);
	jsG_markobject(J, mark, J->ReferenceError_prototype);
	jsG_markobject(J, mark, J->SyntaxError_prototype);
	jsG_markobject(J, mark, J->TypeError_prototype);
	jsG_markobject(J, mark, J->URIError_prototype);

	jsG_markobject(J, mark, J->R);
	jsG_markobject(J, mark, J->G);

	jsG_markstack(J, mark);

	jsG_markenvironment(J, mark, J->E);
	jsG_markenvironment(J, mark, J->GE);
	for (i = 0; i < J->envtop; ++i)
		jsG_markenvironment(J, mark, J->envstack[i]);

	prevnextenv = &J->gcenv;
	for (env = J->gcenv; env; env = nextenv) {
		nextenv = env->gcnext;
		if (env->gcmark != mark) {
			*prevnextenv = nextenv;
			jsG_freeenvironment(J, env);
			++genv;
		} else {
			prevnextenv = &env->gcnext;
		}
		++nenv;
	}

	prevnextfun = &J->gcfun;
	for (fun = J->gcfun; fun; fun = nextfun) {
		nextfun = fun->gcnext;
		if (fun->gcmark != mark) {
			*prevnextfun = nextfun;
			jsG_freefunction(J, fun);
			++gfun;
		} else {
			prevnextfun = &fun->gcnext;
		}
		++nfun;
	}

	prevnextobj = &J->gcobj;
	for (obj = J->gcobj; obj; obj = nextobj) {
		nextobj = obj->gcnext;
		if (obj->gcmark != mark) {
			*prevnextobj = nextobj;
			jsG_freeobject(J, obj);
			++gobj;
		} else {
			prevnextobj = &obj->gcnext;
		}
		++nobj;
	}

	prevnextstr = &J->gcstr;
	for (str = J->gcstr; str; str = nextstr) {
		nextstr = str->gcnext;
		if (str->gcmark != mark) {
			*prevnextstr = nextstr;
			js_free(J, str);
			++gstr;
		} else {
			prevnextstr = &str->gcnext;
		}
		++nstr;
	}

	if (report) {
		char buf[256];
		snprintf(buf, sizeof buf, "garbage collected: %d/%d envs, %d/%d funs, %d/%d objs, %d/%d strs",
			genv, nenv, gfun, nfun, gobj, nobj, gstr, nstr);
		js_report(J, buf);
	}
}