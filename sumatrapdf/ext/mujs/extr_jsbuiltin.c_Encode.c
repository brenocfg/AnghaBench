#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_4__ {char* s; } ;
typedef  TYPE_1__ js_Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  js_endtry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  js_putc (int /*<<< orphan*/ *,TYPE_1__**,char const) ; 
 int /*<<< orphan*/  js_throw (int /*<<< orphan*/ *) ; 
 scalar_t__ js_try (int /*<<< orphan*/ *) ; 
 scalar_t__ strchr (char const*,int) ; 

__attribute__((used)) static void Encode(js_State *J, const char *str, const char *unescaped)
{
	js_Buffer *sb = NULL;

	static const char *HEX = "0123456789ABCDEF";

	if (js_try(J)) {
		js_free(J, sb);
		js_throw(J);
	}

	while (*str) {
		int c = (unsigned char) *str++;
		if (strchr(unescaped, c))
			js_putc(J, &sb, c);
		else {
			js_putc(J, &sb, '%');
			js_putc(J, &sb, HEX[(c >> 4) & 0xf]);
			js_putc(J, &sb, HEX[c & 0xf]);
		}
	}
	js_putc(J, &sb, 0);

	js_pushstring(J, sb ? sb->s : "");
	js_endtry(J);
	js_free(J, sb);
}