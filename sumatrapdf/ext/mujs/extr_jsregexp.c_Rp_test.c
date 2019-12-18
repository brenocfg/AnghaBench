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
struct TYPE_7__ {int flags; scalar_t__ last; int /*<<< orphan*/  prog; } ;
typedef  TYPE_2__ js_Regexp ;
struct TYPE_8__ {TYPE_1__* sub; } ;
struct TYPE_6__ {char const* ep; } ;
typedef  TYPE_3__ Resub ;

/* Variables and functions */
 int JS_REGEXP_G ; 
 int REG_NOTBOL ; 
 int /*<<< orphan*/  js_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  js_pushboolean (int /*<<< orphan*/ *,int) ; 
 int js_regexec (int /*<<< orphan*/ ,char const*,TYPE_3__*,int) ; 
 TYPE_2__* js_toregexp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void Rp_test(js_State *J)
{
	js_Regexp *re;
	const char *text;
	int result;
	int opts;
	Resub m;

	re = js_toregexp(J, 0);
	text = js_tostring(J, 1);

	opts = 0;
	if (re->flags & JS_REGEXP_G) {
		if (re->last > strlen(text)) {
			re->last = 0;
			js_pushboolean(J, 0);
			return;
		}
		if (re->last > 0) {
			text += re->last;
			opts |= REG_NOTBOL;
		}
	}

	result = js_regexec(re->prog, text, &m, opts);
	if (result < 0)
		js_error(J, "regexec failed");
	if (result == 0) {
		if (re->flags & JS_REGEXP_G)
			re->last = re->last + (m.sub[0].ep - text);
		js_pushboolean(J, 1);
		return;
	}

	if (re->flags & JS_REGEXP_G)
		re->last = 0;

	js_pushboolean(J, 0);
}