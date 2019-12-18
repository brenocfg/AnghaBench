#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
typedef  int /*<<< orphan*/  js_Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  fmtindent (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char const*,int) ; 
 int /*<<< orphan*/  fmtvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int) ; 
 int js_getlength (int /*<<< orphan*/ *,int) ; 
 int js_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ js_isobject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_itoa (char*,int) ; 
 int /*<<< orphan*/  js_putc (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char) ; 
 int /*<<< orphan*/  js_puts (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char*) ; 
 scalar_t__ js_toobject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_typeerror (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void fmtarray(js_State *J, js_Buffer **sb, const char *gap, int level)
{
	int n, i;
	char buf[32];

	n = js_gettop(J) - 1;
	for (i = 4; i < n; ++i)
		if (js_isobject(J, i))
			if (js_toobject(J, i) == js_toobject(J, -1))
				js_typeerror(J, "cyclic object value");

	js_putc(J, sb, '[');
	n = js_getlength(J, -1);
	for (i = 0; i < n; ++i) {
		if (i) js_putc(J, sb, ',');
		if (gap) fmtindent(J, sb, gap, level + 1);
		if (!fmtvalue(J, sb, js_itoa(buf, i), gap, level + 1))
			js_puts(J, sb, "null");
	}
	if (gap && n) fmtindent(J, sb, gap, level);
	js_putc(J, sb, ']');
}