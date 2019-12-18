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
 int js_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_iscallable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_typeerror (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void Fp_call(js_State *J)
{
	int i, top = js_gettop(J);

	if (!js_iscallable(J, 0))
		js_typeerror(J, "not a function");

	for (i = 0; i < top; ++i)
		js_copy(J, i);

	js_call(J, top - 2);
}