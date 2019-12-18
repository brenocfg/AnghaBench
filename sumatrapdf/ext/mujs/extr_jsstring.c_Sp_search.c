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
struct TYPE_8__ {TYPE_1__* sub; } ;
struct TYPE_6__ {int /*<<< orphan*/  sp; } ;
typedef  TYPE_3__ Resub ;

/* Variables and functions */
 char* checkstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_copy (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_doregexec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ js_isregexp (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_isundefined (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_newregexp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pushnumber (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* js_toregexp (int /*<<< orphan*/ *,int) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 int js_utfptrtoidx (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Sp_search(js_State *J)
{
	js_Regexp *re;
	const char *text;
	Resub m;

	text = checkstring(J, 0);

	if (js_isregexp(J, 1))
		js_copy(J, 1);
	else if (js_isundefined(J, 1))
		js_newregexp(J, "", 0);
	else
		js_newregexp(J, js_tostring(J, 1), 0);

	re = js_toregexp(J, -1);

	if (!js_doregexec(J, re->prog, text, &m, 0))
		js_pushnumber(J, js_utfptrtoidx(text, m.sub[0].sp));
	else
		js_pushnumber(J, -1);
}