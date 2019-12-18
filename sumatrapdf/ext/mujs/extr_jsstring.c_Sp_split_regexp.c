#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_7__ {int /*<<< orphan*/  prog; } ;
typedef  TYPE_2__ js_Regexp ;
struct TYPE_8__ {int nsub; TYPE_1__* sub; } ;
struct TYPE_6__ {char* sp; char* ep; } ;
typedef  TYPE_3__ Resub ;

/* Variables and functions */
 int /*<<< orphan*/  REG_NOTBOL ; 
 char* checkstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ js_doregexec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ js_isdefined (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_newarray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  js_pushlstring (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  js_setindex (int /*<<< orphan*/ *,int,int) ; 
 int js_tointeger (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* js_toregexp (int /*<<< orphan*/ *,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void Sp_split_regexp(js_State *J)
{
	js_Regexp *re;
	const char *text;
	int limit, len, k;
	const char *p, *a, *b, *c, *e;
	Resub m;

	text = checkstring(J, 0);
	re = js_toregexp(J, 1);
	limit = js_isdefined(J, 2) ? js_tointeger(J, 2) : 1 << 30;

	js_newarray(J);
	len = 0;

	e = text + strlen(text);

	/* splitting the empty string */
	if (e == text) {
		if (js_doregexec(J, re->prog, text, &m, 0)) {
			if (len == limit) return;
			js_pushliteral(J, "");
			js_setindex(J, -2, 0);
		}
		return;
	}

	p = a = text;
	while (a < e) {
		if (js_doregexec(J, re->prog, a, &m, a > text ? REG_NOTBOL : 0))
			break; /* no match */

		b = m.sub[0].sp;
		c = m.sub[0].ep;

		/* empty string at end of last match */
		if (b == p) {
			++a;
			continue;
		}

		if (len == limit) return;
		js_pushlstring(J, p, b - p);
		js_setindex(J, -2, len++);

		for (k = 1; k < m.nsub; ++k) {
			if (len == limit) return;
			js_pushlstring(J, m.sub[k].sp, m.sub[k].ep - m.sub[k].sp);
			js_setindex(J, -2, len++);
		}

		a = p = c;
	}

	if (len == limit) return;
	js_pushstring(J, p);
	js_setindex(J, -2, len);
}