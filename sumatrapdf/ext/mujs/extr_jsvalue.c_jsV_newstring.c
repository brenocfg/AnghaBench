#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  String_prototype; } ;
typedef  TYPE_3__ js_State ;
struct TYPE_10__ {int /*<<< orphan*/  length; int /*<<< orphan*/  string; } ;
struct TYPE_11__ {TYPE_1__ s; } ;
struct TYPE_13__ {TYPE_2__ u; } ;
typedef  TYPE_4__ js_Object ;

/* Variables and functions */
 int /*<<< orphan*/  JS_CSTRING ; 
 TYPE_4__* jsV_newobject (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_intern (TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  utflen (char const*) ; 

__attribute__((used)) static js_Object *jsV_newstring(js_State *J, const char *v)
{
	js_Object *obj = jsV_newobject(J, JS_CSTRING, J->String_prototype);
	obj->u.s.string = js_intern(J, v); /* TODO: js_String */
	obj->u.s.length = utflen(v);
	return obj;
}