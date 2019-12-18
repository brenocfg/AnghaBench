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
 int /*<<< orphan*/  js_getindex (int /*<<< orphan*/ *,int,int) ; 
 int js_getlength (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_iscallable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ js_isnull (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_isundefined (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_typeerror (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void Fp_apply(js_State *J)
{
	int i, n;

	if (!js_iscallable(J, 0))
		js_typeerror(J, "not a function");

	js_copy(J, 0);
	js_copy(J, 1);

	if (js_isnull(J, 2) || js_isundefined(J, 2)) {
		n = 0;
	} else {
		n = js_getlength(J, 2);
		for (i = 0; i < n; ++i)
			js_getindex(J, 2, i);
	}

	js_call(J, n);
}