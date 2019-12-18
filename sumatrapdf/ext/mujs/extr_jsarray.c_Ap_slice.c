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
 int js_getlength (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ js_hasindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ js_isdefined (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_newarray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_setindex (int /*<<< orphan*/ *,int,int) ; 
 int js_tointeger (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void Ap_slice(js_State *J)
{
	int len, s, e, n;
	double sv, ev;

	js_newarray(J);

	len = js_getlength(J, 0);
	sv = js_tointeger(J, 1);
	ev = js_isdefined(J, 2) ? js_tointeger(J, 2) : len;

	if (sv < 0) sv = sv + len;
	if (ev < 0) ev = ev + len;

	s = sv < 0 ? 0 : sv > len ? len : sv;
	e = ev < 0 ? 0 : ev > len ? len : ev;

	for (n = 0; s < e; ++s, ++n)
		if (js_hasindex(J, 0, s))
			js_setindex(J, -2, n);
}