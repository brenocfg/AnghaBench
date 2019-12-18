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
typedef  int Rune ;

/* Variables and functions */
 int /*<<< orphan*/  chartorune (int*,char const*) ; 
 scalar_t__ minify ; 
 int /*<<< orphan*/  pc (char const) ; 
 int /*<<< orphan*/  ps (char*) ; 

__attribute__((used)) static void pstr(const char *s)
{
	static const char *HEX = "0123456789ABCDEF";
	Rune c;
	pc(minify ? '\'' : '"');
	while (*s) {
		s += chartorune(&c, s);
		switch (c) {
		case '\'': ps("\\'"); break;
		case '"': ps("\\\""); break;
		case '\\': ps("\\\\"); break;
		case '\b': ps("\\b"); break;
		case '\f': ps("\\f"); break;
		case '\n': ps("\\n"); break;
		case '\r': ps("\\r"); break;
		case '\t': ps("\\t"); break;
		default:
			if (c < ' ' || c > 127) {
				ps("\\u");
				pc(HEX[(c>>12)&15]);
				pc(HEX[(c>>8)&15]);
				pc(HEX[(c>>4)&15]);
				pc(HEX[c&15]);
			} else {
				pc(c); break;
			}
		}
	}
	pc(minify ? '\'' : '"');
}