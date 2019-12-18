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
 scalar_t__ js_isdefined (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushlstring (int /*<<< orphan*/ *,char const*,int) ; 
 int js_tointeger (int /*<<< orphan*/ *,int) ; 
 char* js_utfidxtoptr (char const*,int) ; 
 int utflen (char const*) ; 

__attribute__((used)) static void Sp_slice(js_State *J)
{
	const char *str = checkstring(J, 0);
	const char *ss, *ee;
	int len = utflen(str);
	int s = js_tointeger(J, 1);
	int e = js_isdefined(J, 2) ? js_tointeger(J, 2) : len;

	s = s < 0 ? s + len : s;
	e = e < 0 ? e + len : e;

	s = s < 0 ? 0 : s > len ? len : s;
	e = e < 0 ? 0 : e > len ? len : e;

	if (s < e) {
		ss = js_utfidxtoptr(str, s);
		ee = js_utfidxtoptr(ss, e - s);
	} else {
		ss = js_utfidxtoptr(str, e);
		ee = js_utfidxtoptr(ss, s - e);
	}

	js_pushlstring(J, ss, ee - ss);
}