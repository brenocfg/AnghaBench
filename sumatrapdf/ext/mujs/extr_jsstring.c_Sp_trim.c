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

/* Variables and functions */
 char* checkstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ istrim (char const) ; 
 int /*<<< orphan*/  js_pushlstring (int /*<<< orphan*/ *,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void Sp_trim(js_State *J)
{
	const char *s, *e;
	s = checkstring(J, 0);
	while (istrim(*s))
		++s;
	e = s + strlen(s);
	while (e > s && istrim(e[-1]))
		--e;
	js_pushlstring(J, s, e - s);
}