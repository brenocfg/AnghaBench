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
 int /*<<< orphan*/  js_construct (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_copy (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_currentfunction (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_getindex (int /*<<< orphan*/ *,int,int) ; 
 int js_getlength (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_getproperty (int /*<<< orphan*/ *,int,char*) ; 
 int js_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_remove (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void constructbound(js_State *J)
{
	int top = js_gettop(J);
	int i, fun, args, n;

	fun = js_gettop(J);
	js_currentfunction(J);
	js_getproperty(J, fun, "__TargetFunction__");

	args = js_gettop(J);
	js_getproperty(J, fun, "__BoundArguments__");
	n = js_getlength(J, args);
	for (i = 0; i < n; ++i)
		js_getindex(J, args, i);
	js_remove(J, args);

	for (i = 1; i < top; ++i)
		js_copy(J, i);

	js_construct(J, n + top - 1);
}