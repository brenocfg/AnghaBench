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
 int /*<<< orphan*/  chartorune (int /*<<< orphan*/ *,char const*) ; 
 char* checkstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pushnumber (int /*<<< orphan*/ *,int) ; 
 int js_tointeger (int /*<<< orphan*/ *,int) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int) ; 

__attribute__((used)) static void Sp_indexOf(js_State *J)
{
	const char *haystack = checkstring(J, 0);
	const char *needle = js_tostring(J, 1);
	int pos = js_tointeger(J, 2);
	int len = strlen(needle);
	int k = 0;
	Rune rune;
	while (*haystack) {
		if (k >= pos && !strncmp(haystack, needle, len)) {
			js_pushnumber(J, k);
			return;
		}
		haystack += chartorune(&rune, haystack);
		++k;
	}
	js_pushnumber(J, -1);
}