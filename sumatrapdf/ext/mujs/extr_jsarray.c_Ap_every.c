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
 int /*<<< orphan*/  js_call (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_copy (int /*<<< orphan*/ *,int) ; 
 int js_getlength (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int js_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ js_hasindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  js_iscallable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushundefined (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_toboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_typeerror (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void Ap_every(js_State *J)
{
	int hasthis = js_gettop(J) >= 3;
	int k, len;

	if (!js_iscallable(J, 1))
		js_typeerror(J, "callback is not a function");

	len = js_getlength(J, 0);
	for (k = 0; k < len; ++k) {
		if (js_hasindex(J, 0, k)) {
			js_copy(J, 1);
			if (hasthis)
				js_copy(J, 2);
			else
				js_pushundefined(J);
			js_copy(J, -3);
			js_pushnumber(J, k);
			js_copy(J, 0);
			js_call(J, 3);
			if (!js_toboolean(J, -1))
				return;
			js_pop(J, 2);
		}
	}

	js_pushboolean(J, 1);
}