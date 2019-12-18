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
 int /*<<< orphan*/  js_getproperty (int /*<<< orphan*/ *,int,char const*) ; 
 int js_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ js_isobject (int /*<<< orphan*/ *,int) ; 
 char* js_nextiterator (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushiterator (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  js_putc (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char) ; 
 int /*<<< orphan*/  js_puts (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char*) ; 
 scalar_t__ js_toobject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  reprident (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char const*) ; 
 int /*<<< orphan*/  reprvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void reprobject(js_State *J, js_Buffer **sb)
{
	const char *key;
	int i, n;

	n = js_gettop(J) - 1;
	for (i = 0; i < n; ++i) {
		if (js_isobject(J, i)) {
			if (js_toobject(J, i) == js_toobject(J, -1)) {
				js_puts(J, sb, "{}");
				return;
			}
		}
	}

	n = 0;
	js_putc(J, sb, '{');
	js_pushiterator(J, -1, 1);
	while ((key = js_nextiterator(J, -1))) {
		if (n++ > 0)
			js_puts(J, sb, ", ");
		reprident(J, sb, key);
		js_puts(J, sb, ": ");
		js_getproperty(J, -2, key);
		reprvalue(J, sb);
		js_pop(J, 1);
	}
	js_pop(J, 1);
	js_putc(J, sb, '}');
}