#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
typedef  int /*<<< orphan*/  js_Object ;
struct TYPE_7__ {int n; } ;
typedef  TYPE_1__ js_Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  fmtindent (int /*<<< orphan*/ *,TYPE_1__**,char const*,int) ; 
 int /*<<< orphan*/  fmtstr (int /*<<< orphan*/ *,TYPE_1__**,char const*) ; 
 int /*<<< orphan*/  fmtvalue (int /*<<< orphan*/ *,TYPE_1__**,char const*,char const*,int) ; 
 int js_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ js_isobject (int /*<<< orphan*/ *,int) ; 
 char* js_nextiterator (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushiterator (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  js_putc (int /*<<< orphan*/ *,TYPE_1__**,char) ; 
 int /*<<< orphan*/  js_rot2 (int /*<<< orphan*/ *) ; 
 scalar_t__ js_toobject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_typeerror (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void fmtobject(js_State *J, js_Buffer **sb, js_Object *obj, const char *gap, int level)
{
	const char *key;
	int save;
	int i, n;

	n = js_gettop(J) - 1;
	for (i = 4; i < n; ++i)
		if (js_isobject(J, i))
			if (js_toobject(J, i) == js_toobject(J, -1))
				js_typeerror(J, "cyclic object value");

	n = 0;
	js_putc(J, sb, '{');
	js_pushiterator(J, -1, 1);
	while ((key = js_nextiterator(J, -1))) {
		save = (*sb)->n;
		if (n) js_putc(J, sb, ',');
		if (gap) fmtindent(J, sb, gap, level + 1);
		fmtstr(J, sb, key);
		js_putc(J, sb, ':');
		if (gap)
			js_putc(J, sb, ' ');
		js_rot2(J);
		if (!fmtvalue(J, sb, key, gap, level + 1))
			(*sb)->n = save;
		else
			++n;
		js_rot2(J);
	}
	js_pop(J, 1);
	if (gap && n) fmtindent(J, sb, gap, level);
	js_putc(J, sb, '}');
}