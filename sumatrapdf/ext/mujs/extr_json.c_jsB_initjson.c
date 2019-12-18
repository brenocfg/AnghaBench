#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  Object_prototype; } ;
typedef  TYPE_1__ js_State ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_parse ; 
 int /*<<< orphan*/  JSON_stringify ; 
 int /*<<< orphan*/  JS_CJSON ; 
 int /*<<< orphan*/  JS_DONTENUM ; 
 int /*<<< orphan*/  jsB_propf (TYPE_1__*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jsV_newobject (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_defglobal (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pushobject (TYPE_1__*,int /*<<< orphan*/ ) ; 

void jsB_initjson(js_State *J)
{
	js_pushobject(J, jsV_newobject(J, JS_CJSON, J->Object_prototype));
	{
		jsB_propf(J, "JSON.parse", JSON_parse, 2);
		jsB_propf(J, "JSON.stringify", JSON_stringify, 3);
	}
	js_defglobal(J, "JSON", JS_DONTENUM);
}