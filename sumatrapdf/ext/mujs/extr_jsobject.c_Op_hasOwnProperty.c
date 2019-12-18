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
typedef  int /*<<< orphan*/  js_Property ;
typedef  int /*<<< orphan*/  js_Object ;

/* Variables and functions */
 int /*<<< orphan*/ * jsV_getownproperty (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  js_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * js_toobject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void Op_hasOwnProperty(js_State *J)
{
	js_Object *self = js_toobject(J, 0);
	const char *name = js_tostring(J, 1);
	js_Property *ref = jsV_getownproperty(J, self, name);
	js_pushboolean(J, ref != NULL);
}