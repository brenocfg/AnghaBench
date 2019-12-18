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
typedef  scalar_t__ Rune ;

/* Variables and functions */
 int /*<<< orphan*/  UTFmax ; 
 char* checkstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ js_runeat (int /*<<< orphan*/ *,char const*,int) ; 
 int js_tointeger (int /*<<< orphan*/ *,int) ; 
 size_t runetochar (char*,scalar_t__*) ; 

__attribute__((used)) static void Sp_charAt(js_State *J)
{
	char buf[UTFmax + 1];
	const char *s = checkstring(J, 0);
	int pos = js_tointeger(J, 1);
	Rune rune = js_runeat(J, s, pos);
	if (rune > 0) {
		buf[runetochar(buf, &rune)] = 0;
		js_pushstring(J, buf);
	} else {
		js_pushliteral(J, "");
	}
}