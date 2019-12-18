#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_8__ {int flags; int /*<<< orphan*/  prog; scalar_t__ last; } ;
typedef  TYPE_2__ js_Regexp ;
struct TYPE_9__ {TYPE_1__* sub; } ;
struct TYPE_7__ {char* sp; char* ep; } ;
typedef  TYPE_3__ Resub ;

/* Variables and functions */
 int JS_REGEXP_G ; 
 int /*<<< orphan*/  REG_NOTBOL ; 
 char* checkstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_RegExp_prototype_exec (int /*<<< orphan*/ *,TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  js_copy (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_doregexec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ js_isregexp (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_isundefined (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_newarray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_newregexp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushlstring (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  js_pushnull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_setindex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* js_toregexp (int /*<<< orphan*/ *,int) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void Sp_match(js_State *J)
{
	js_Regexp *re;
	const char *text;
	int len;
	const char *a, *b, *c, *e;
	Resub m;

	text = checkstring(J, 0);

	if (js_isregexp(J, 1))
		js_copy(J, 1);
	else if (js_isundefined(J, 1))
		js_newregexp(J, "", 0);
	else
		js_newregexp(J, js_tostring(J, 1), 0);

	re = js_toregexp(J, -1);
	if (!(re->flags & JS_REGEXP_G)) {
		js_RegExp_prototype_exec(J, re, text);
		return;
	}

	re->last = 0;

	js_newarray(J);

	len = 0;
	a = text;
	e = text + strlen(text);
	while (a <= e) {
		if (js_doregexec(J, re->prog, a, &m, a > text ? REG_NOTBOL : 0))
			break;

		b = m.sub[0].sp;
		c = m.sub[0].ep;

		js_pushlstring(J, b, c - b);
		js_setindex(J, -2, len++);

		a = c;
		if (c - b == 0)
			++a;
	}

	if (len == 0) {
		js_pop(J, 1);
		js_pushnull(J);
	}
}