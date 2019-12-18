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
 int js_getlength (int /*<<< orphan*/ *,int) ; 
 int js_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ js_hasindex (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ js_isarray (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_newarray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_setindex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Ap_concat(js_State *J)
{
	int i, top = js_gettop(J);
	int n, k, len;

	js_newarray(J);
	n = 0;

	for (i = 0; i < top; ++i) {
		js_copy(J, i);
		if (js_isarray(J, -1)) {
			len = js_getlength(J, -1);
			for (k = 0; k < len; ++k)
				if (js_hasindex(J, -1, k))
					js_setindex(J, -3, n++);
			js_pop(J, 1);
		} else {
			js_setindex(J, -2, n++);
		}
	}
}