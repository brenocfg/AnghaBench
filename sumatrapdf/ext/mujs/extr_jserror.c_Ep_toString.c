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
 int /*<<< orphan*/  js_concat (int /*<<< orphan*/ *) ; 
 scalar_t__ js_hasproperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  js_isobject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,char const*) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_typeerror (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void Ep_toString(js_State *J)
{
	const char *name = "Error";
	const char *message = "";

	if (!js_isobject(J, -1))
		js_typeerror(J, "not an object");

	if (js_hasproperty(J, 0, "name"))
		name = js_tostring(J, -1);
	if (js_hasproperty(J, 0, "message"))
		message = js_tostring(J, -1);

	if (name[0] == 0)
		js_pushstring(J, message);
	else if (message[0] == 0)
		js_pushstring(J, name);
	else {
		js_pushstring(J, name);
		js_pushstring(J, ": ");
		js_concat(J);
		js_pushstring(J, message);
		js_concat(J);
	}
}