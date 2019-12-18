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
 int /*<<< orphan*/  js_endtry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_free (int /*<<< orphan*/ *,char*) ; 
 int js_gettop (int /*<<< orphan*/ *) ; 
 char* js_malloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  js_throw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_touint16 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_try (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  runetochar (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void S_fromCharCode(js_State *J)
{
	int i, top = js_gettop(J);
	Rune c;
	char *s, *p;

	s = p = js_malloc(J, (top-1) * UTFmax + 1);

	if (js_try(J)) {
		js_free(J, s);
		js_throw(J);
	}

	for (i = 1; i < top; ++i) {
		c = js_touint16(J, i);
		p += runetochar(p, &c);
	}
	*p = 0;
	js_pushstring(J, s);

	js_endtry(J);
	js_free(J, s);
}