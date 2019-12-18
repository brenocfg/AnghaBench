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
 int /*<<< orphan*/  js_newarray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_setindex (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  js_setlength (int /*<<< orphan*/ *,int,int) ; 
 double js_tointeger (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void Ap_splice(js_State *J)
{
	int top = js_gettop(J);
	int len, start, del, add, k;
	double f;

	js_newarray(J);

	len = js_getlength(J, 0);

	f = js_tointeger(J, 1);
	if (f < 0) f = f + len;
	start = f < 0 ? 0 : f > len ? len : f;

	f = js_tointeger(J, 2);
	del = f < 0 ? 0 : f > len - start ? len - start : f;

	/* copy deleted items to return array */
	for (k = 0; k < del; ++k)
		if (js_hasindex(J, 0, start + k))
			js_setindex(J, -2, k);
	js_setlength(J, -1, del);

	/* shift the tail to resize the hole left by deleted items */
	add = top - 3;
	if (add < del) {
		for (k = start; k < len - del; ++k) {
			if (js_hasindex(J, 0, k + del))
				js_setindex(J, 0, k + add);
			else
				js_delindex(J, 0, k + add);
		}
		for (k = len; k > len - del + add; --k)
			js_delindex(J, 0, k - 1);
	} else if (add > del) {
		for (k = len - del; k > start; --k) {
			if (js_hasindex(J, 0, k + del - 1))
				js_setindex(J, 0, k + add - 1);
			else
				js_delindex(J, 0, k + add - 1);
		}
	}

	/* copy new items into the hole */
	for (k = 0; k < add; ++k) {
		js_copy(J, 3 + k);
		js_setindex(J, 0, start + k);
	}

	js_setlength(J, 0, len - del + add);
}