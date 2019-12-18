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
 int /*<<< orphan*/  jsY_ishex (int) ; 
 int jsY_tohex (int) ; 
 int /*<<< orphan*/  js_endtry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  js_putc (int /*<<< orphan*/ *,TYPE_1__**,int) ; 
 int /*<<< orphan*/  js_throw (int /*<<< orphan*/ *) ; 
 scalar_t__ js_try (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_urierror (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strchr (char const*,int) ; 

__attribute__((used)) static void Decode(js_State *J, const char *str, const char *reserved)
{
	js_Buffer *sb = NULL;
	int a, b;

	if (js_try(J)) {
		js_free(J, sb);
		js_throw(J);
	}

	while (*str) {
		int c = (unsigned char) *str++;
		if (c != '%')
			js_putc(J, &sb, c);
		else {
			if (!str[0] || !str[1])
				js_urierror(J, "truncated escape sequence");
			a = *str++;
			b = *str++;
			if (!jsY_ishex(a) || !jsY_ishex(b))
				js_urierror(J, "invalid escape sequence");
			c = jsY_tohex(a) << 4 | jsY_tohex(b);
			if (!strchr(reserved, c))
				js_putc(J, &sb, c);
			else {
				js_putc(J, &sb, '%');
				js_putc(J, &sb, a);
				js_putc(J, &sb, b);
			}
		}
	}
	js_putc(J, &sb, 0);

	js_pushstring(J, sb ? sb->s : "");
	js_endtry(J);
	js_free(J, sb);
}