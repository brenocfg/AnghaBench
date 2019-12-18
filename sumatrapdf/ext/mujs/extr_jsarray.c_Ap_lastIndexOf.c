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
 int /*<<< orphan*/  js_copy (int /*<<< orphan*/ *,int) ; 
 int js_getlength (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ js_hasindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ js_isdefined (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushnumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_strictequal (int /*<<< orphan*/ *) ; 
 int js_tointeger (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void Ap_lastIndexOf(js_State *J)
{
	int k, len, from;

	len = js_getlength(J, 0);
	from = js_isdefined(J, 2) ? js_tointeger(J, 2) : len - 1;
	if (from > len - 1) from = len - 1;
	if (from < 0) from = len + from;

	js_copy(J, 1);
	for (k = from; k >= 0; --k) {
		if (js_hasindex(J, 0, k)) {
			if (js_strictequal(J)) {
				js_pushnumber(J, k);
				return;
			}
			js_pop(J, 1);
		}
	}

	js_pushnumber(J, -1);
}