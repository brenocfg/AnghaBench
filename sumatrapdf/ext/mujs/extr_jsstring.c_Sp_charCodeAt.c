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
 scalar_t__ NAN ; 
 char* checkstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pushnumber (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ js_runeat (int /*<<< orphan*/ *,char const*,int) ; 
 int js_tointeger (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void Sp_charCodeAt(js_State *J)
{
	const char *s = checkstring(J, 0);
	int pos = js_tointeger(J, 1);
	Rune rune = js_runeat(J, s, pos);
	if (rune > 0)
		js_pushnumber(J, rune);
	else
		js_pushnumber(J, NAN);
}