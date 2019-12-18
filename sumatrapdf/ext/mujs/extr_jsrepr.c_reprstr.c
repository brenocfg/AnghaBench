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
typedef  int Rune ;

/* Variables and functions */
 int /*<<< orphan*/  chartorune (int*,char const*) ; 
 int /*<<< orphan*/  js_putc (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char const) ; 
 int /*<<< orphan*/  js_puts (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char*) ; 

__attribute__((used)) static void reprstr(js_State *J, js_Buffer **sb, const char *s)
{
	static const char *HEX = "0123456789ABCDEF";
	Rune c;
	js_putc(J, sb, '"');
	while (*s) {
		s += chartorune(&c, s);
		switch (c) {
		case '"': js_puts(J, sb, "\\\""); break;
		case '\\': js_puts(J, sb, "\\\\"); break;
		case '\b': js_puts(J, sb, "\\b"); break;
		case '\f': js_puts(J, sb, "\\f"); break;
		case '\n': js_puts(J, sb, "\\n"); break;
		case '\r': js_puts(J, sb, "\\r"); break;
		case '\t': js_puts(J, sb, "\\t"); break;
		default:
			if (c < ' ' || c > 127) {
				js_puts(J, sb, "\\u");
				js_putc(J, sb, HEX[(c>>12)&15]);
				js_putc(J, sb, HEX[(c>>8)&15]);
				js_putc(J, sb, HEX[(c>>4)&15]);
				js_putc(J, sb, HEX[c&15]);
			} else {
				js_putc(J, sb, c); break;
			}
		}
	}
	js_putc(J, sb, '"');
}