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
 int /*<<< orphan*/  JS_DONTENUM ; 
 int /*<<< orphan*/  O_create ; 
 int /*<<< orphan*/  O_defineProperties ; 
 int /*<<< orphan*/  O_defineProperty ; 
 int /*<<< orphan*/  O_freeze ; 
 int /*<<< orphan*/  O_getOwnPropertyDescriptor ; 
 int /*<<< orphan*/  O_getOwnPropertyNames ; 
 int /*<<< orphan*/  O_getPrototypeOf ; 
 int /*<<< orphan*/  O_isExtensible ; 
 int /*<<< orphan*/  O_isFrozen ; 
 int /*<<< orphan*/  O_isSealed ; 
 int /*<<< orphan*/  O_keys ; 
 int /*<<< orphan*/  O_preventExtensions ; 
 int /*<<< orphan*/  O_seal ; 
 int /*<<< orphan*/  Op_hasOwnProperty ; 
 int /*<<< orphan*/  Op_isPrototypeOf ; 
 int /*<<< orphan*/  Op_propertyIsEnumerable ; 
 int /*<<< orphan*/  Op_toString ; 
 int /*<<< orphan*/  Op_valueOf ; 
 int /*<<< orphan*/  jsB_Object ; 
 int /*<<< orphan*/  jsB_new_Object ; 
 int /*<<< orphan*/  jsB_propf (TYPE_1__*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  js_defglobal (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_newcconstructor (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  js_pushobject (TYPE_1__*,int /*<<< orphan*/ ) ; 

void jsB_initobject(js_State *J)
{
	js_pushobject(J, J->Object_prototype);
	{
		jsB_propf(J, "Object.prototype.toString", Op_toString, 0);
		jsB_propf(J, "Object.prototype.toLocaleString", Op_toString, 0);
		jsB_propf(J, "Object.prototype.valueOf", Op_valueOf, 0);
		jsB_propf(J, "Object.prototype.hasOwnProperty", Op_hasOwnProperty, 1);
		jsB_propf(J, "Object.prototype.isPrototypeOf", Op_isPrototypeOf, 1);
		jsB_propf(J, "Object.prototype.propertyIsEnumerable", Op_propertyIsEnumerable, 1);
	}
	js_newcconstructor(J, jsB_Object, jsB_new_Object, "Object", 1);
	{
		/* ES5 */
		jsB_propf(J, "Object.getPrototypeOf", O_getPrototypeOf, 1);
		jsB_propf(J, "Object.getOwnPropertyDescriptor", O_getOwnPropertyDescriptor, 2);
		jsB_propf(J, "Object.getOwnPropertyNames", O_getOwnPropertyNames, 1);
		jsB_propf(J, "Object.create", O_create, 2);
		jsB_propf(J, "Object.defineProperty", O_defineProperty, 3);
		jsB_propf(J, "Object.defineProperties", O_defineProperties, 2);
		jsB_propf(J, "Object.seal", O_seal, 1);
		jsB_propf(J, "Object.freeze", O_freeze, 1);
		jsB_propf(J, "Object.preventExtensions", O_preventExtensions, 1);
		jsB_propf(J, "Object.isSealed", O_isSealed, 1);
		jsB_propf(J, "Object.isFrozen", O_isFrozen, 1);
		jsB_propf(J, "Object.isExtensible", O_isExtensible, 1);
		jsB_propf(J, "Object.keys", O_keys, 1);
	}
	js_defglobal(J, "Object", JS_DONTENUM);
}