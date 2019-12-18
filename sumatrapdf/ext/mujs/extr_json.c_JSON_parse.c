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
 int /*<<< orphan*/  jsY_initlex (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  js_defproperty (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ js_iscallable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_newobject (int /*<<< orphan*/ *) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jsonnext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsonrevive (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  jsonvalue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void JSON_parse(js_State *J)
{
	const char *source = js_tostring(J, 1);
	jsY_initlex(J, "JSON", source);
	jsonnext(J);

	if (js_iscallable(J, 2)) {
		js_newobject(J);
		jsonvalue(J);
		js_defproperty(J, -2, "", 0);
		jsonrevive(J, "");
	} else {
		jsonvalue(J);
	}
}