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
 int /*<<< orphan*/  js_delindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int js_getlength (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int js_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ js_hasindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  js_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_setindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  js_setlength (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void Ap_unshift(js_State *J)
{
	int i, top = js_gettop(J);
	int k, len;

	len = js_getlength(J, 0);

	for (k = len; k > 0; --k) {
		int from = k - 1;
		int to = k + top - 2;
		if (js_hasindex(J, 0, from))
			js_setindex(J, 0, to);
		else
			js_delindex(J, 0, to);
	}

	for (i = 1; i < top; ++i) {
		js_copy(J, i);
		js_setindex(J, 0, i - 1);
	}

	js_setlength(J, 0, len + top - 1);

	js_pushnumber(J, len + top - 1);
}