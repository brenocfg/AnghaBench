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
 int /*<<< orphan*/  js_delindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  js_getindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int js_getlength (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ js_hasindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  js_pushundefined (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_setindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  js_setlength (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void Ap_shift(js_State *J)
{
	int k, len;

	len = js_getlength(J, 0);

	if (len == 0) {
		js_setlength(J, 0, 0);
		js_pushundefined(J);
		return;
	}

	js_getindex(J, 0, 0);

	for (k = 1; k < len; ++k) {
		if (js_hasindex(J, 0, k))
			js_setindex(J, 0, k - 1);
		else
			js_delindex(J, 0, k - 1);
	}

	js_delindex(J, 0, len - 1);
	js_setlength(J, 0, len - 1);
}