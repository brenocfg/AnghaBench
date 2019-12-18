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
 int /*<<< orphan*/  js_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_delindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int js_getlength (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int js_hasindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  js_setindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void Ap_reverse(js_State *J)
{
	int len, middle, lower;

	len = js_getlength(J, 0);
	middle = len / 2;
	lower = 0;

	while (lower != middle) {
		int upper = len - lower - 1;
		int haslower = js_hasindex(J, 0, lower);
		int hasupper = js_hasindex(J, 0, upper);
		if (haslower && hasupper) {
			js_setindex(J, 0, lower);
			js_setindex(J, 0, upper);
		} else if (hasupper) {
			js_setindex(J, 0, lower);
			js_delindex(J, 0, upper);
		} else if (haslower) {
			js_setindex(J, 0, upper);
			js_delindex(J, 0, lower);
		}
		++lower;
	}

	js_copy(J, 0);
}