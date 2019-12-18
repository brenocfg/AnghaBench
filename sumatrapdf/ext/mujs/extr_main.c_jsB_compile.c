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
 scalar_t__ js_isdefined (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_loadstring (int /*<<< orphan*/ *,char const*,char const*) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void jsB_compile(js_State *J)
{
	const char *source = js_tostring(J, 1);
	const char *filename = js_isdefined(J, 2) ? js_tostring(J, 2) : "[string]";
	js_loadstring(J, filename, source);
}