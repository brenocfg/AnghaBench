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
typedef  int /*<<< orphan*/  Rune ;

/* Variables and functions */
 int chartorune (int /*<<< orphan*/ *,char const*) ; 
 char* checkstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ js_isdefined (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_newarray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pushlstring (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  js_setindex (int /*<<< orphan*/ *,int,int) ; 
 int js_tointeger (int /*<<< orphan*/ *,int) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 int strlen (char const*) ; 
 char* strstr (char const*,char const*) ; 

__attribute__((used)) static void Sp_split_string(js_State *J)
{
	const char *str = checkstring(J, 0);
	const char *sep = js_tostring(J, 1);
	int limit = js_isdefined(J, 2) ? js_tointeger(J, 2) : 1 << 30;
	int i, n;

	js_newarray(J);

	n = strlen(sep);

	/* empty string */
	if (n == 0) {
		Rune rune;
		for (i = 0; *str && i < limit; ++i) {
			n = chartorune(&rune, str);
			js_pushlstring(J, str, n);
			js_setindex(J, -2, i);
			str += n;
		}
		return;
	}

	for (i = 0; str && i < limit; ++i) {
		const char *s = strstr(str, sep);
		if (s) {
			js_pushlstring(J, str, s-str);
			js_setindex(J, -2, i);
			str = s + n;
		} else {
			js_pushstring(J, str);
			js_setindex(J, -2, i);
			str = NULL;
		}
	}
}