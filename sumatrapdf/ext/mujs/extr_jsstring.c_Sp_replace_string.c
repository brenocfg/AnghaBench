#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_6__ {char* s; } ;
typedef  TYPE_1__ js_Buffer ;

/* Variables and functions */
 char* checkstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_call (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_copy (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_endtry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ js_iscallable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushlstring (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  js_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  js_pushundefined (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_putc (int /*<<< orphan*/ *,TYPE_1__**,char const) ; 
 int /*<<< orphan*/  js_putm (int /*<<< orphan*/ *,TYPE_1__**,char const*,char const*) ; 
 int /*<<< orphan*/  js_puts (int /*<<< orphan*/ *,TYPE_1__**,char const*) ; 
 int /*<<< orphan*/  js_throw (int /*<<< orphan*/ *) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_try (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 char* strstr (char const*,char const*) ; 

__attribute__((used)) static void Sp_replace_string(js_State *J)
{
	const char *source, *needle, *s, *r;
	js_Buffer *sb = NULL;
	int n;

	source = checkstring(J, 0);
	needle = js_tostring(J, 1);

	s = strstr(source, needle);
	if (!s) {
		js_copy(J, 0);
		return;
	}
	n = strlen(needle);

	if (js_iscallable(J, 2)) {
		js_copy(J, 2);
		js_pushundefined(J);
		js_pushlstring(J, s, n); /* arg 1: substring that matched */
		js_pushnumber(J, s - source); /* arg 2: offset within search string */
		js_copy(J, 0); /* arg 3: search string */
		js_call(J, 3);
		r = js_tostring(J, -1);
		js_putm(J, &sb, source, s);
		js_puts(J, &sb, r);
		js_puts(J, &sb, s + n);
		js_putc(J, &sb, 0);
		js_pop(J, 1);
	} else {
		r = js_tostring(J, 2);
		js_putm(J, &sb, source, s);
		while (*r) {
			if (*r == '$') {
				switch (*(++r)) {
				case 0: --r; /* end of string; back up */
				/* fallthrough */
				case '$': js_putc(J, &sb, '$'); break;
				case '&': js_putm(J, &sb, s, s + n); break;
				case '`': js_putm(J, &sb, source, s); break;
				case '\'': js_puts(J, &sb, s + n); break;
				default: js_putc(J, &sb, '$'); js_putc(J, &sb, *r); break;
				}
				++r;
			} else {
				js_putc(J, &sb, *r++);
			}
		}
		js_puts(J, &sb, s + n);
		js_putc(J, &sb, 0);
	}

	if (js_try(J)) {
		js_free(J, sb);
		js_throw(J);
	}
	js_pushstring(J, sb ? sb->s : "");
	js_endtry(J);
	js_free(J, sb);
}