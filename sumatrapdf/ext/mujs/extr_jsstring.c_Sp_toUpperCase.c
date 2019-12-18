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
 int UTFmax ; 
 int /*<<< orphan*/  chartorune (int /*<<< orphan*/ *,char const*) ; 
 char* checkstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_endtry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_free (int /*<<< orphan*/ *,char*) ; 
 char* js_malloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  js_throw (int /*<<< orphan*/ *) ; 
 scalar_t__ js_try (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  runetochar (char*,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  toupperrune (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Sp_toUpperCase(js_State *J)
{
	const char *src = checkstring(J, 0);
	char *dst = js_malloc(J, UTFmax * strlen(src) + 1);
	const char *s = src;
	char *d = dst;
	Rune rune;
	while (*s) {
		s += chartorune(&rune, s);
		rune = toupperrune(rune);
		d += runetochar(d, &rune);
	}
	*d = 0;
	if (js_try(J)) {
		js_free(J, dst);
		js_throw(J);
	}
	js_pushstring(J, dst);
	js_endtry(J);
	js_free(J, dst);
}