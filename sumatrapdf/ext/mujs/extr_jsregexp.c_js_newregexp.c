#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  actx; int /*<<< orphan*/  alloc; int /*<<< orphan*/  RegExp_prototype; } ;
typedef  TYPE_3__ js_State ;
struct TYPE_12__ {int flags; scalar_t__ last; int /*<<< orphan*/  source; int /*<<< orphan*/ * prog; } ;
struct TYPE_13__ {TYPE_1__ r; } ;
struct TYPE_15__ {TYPE_2__ u; } ;
typedef  TYPE_4__ js_Object ;
typedef  int /*<<< orphan*/  Reprog ;

/* Variables and functions */
 int /*<<< orphan*/  JS_CREGEXP ; 
 int JS_REGEXP_I ; 
 int JS_REGEXP_M ; 
 int REG_ICASE ; 
 int REG_NEWLINE ; 
 TYPE_4__* jsV_newobject (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pushobject (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/ * js_regcompx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,char const**) ; 
 int /*<<< orphan*/  js_strdup (TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  js_syntaxerror (TYPE_3__*,char*,char const*) ; 

void js_newregexp(js_State *J, const char *pattern, int flags)
{
	const char *error;
	js_Object *obj;
	Reprog *prog;
	int opts;

	obj = jsV_newobject(J, JS_CREGEXP, J->RegExp_prototype);

	opts = 0;
	if (flags & JS_REGEXP_I) opts |= REG_ICASE;
	if (flags & JS_REGEXP_M) opts |= REG_NEWLINE;

	prog = js_regcompx(J->alloc, J->actx, pattern, opts, &error);
	if (!prog)
		js_syntaxerror(J, "regular expression: %s", error);

	obj->u.r.prog = prog;
	obj->u.r.source = js_strdup(J, pattern);
	obj->u.r.flags = flags;
	obj->u.r.last = 0;
	js_pushobject(J, obj);
}