#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_5__* String_prototype; } ;
typedef  TYPE_3__ js_State ;
struct TYPE_10__ {char* string; scalar_t__ length; } ;
struct TYPE_11__ {TYPE_1__ s; } ;
struct TYPE_13__ {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  JS_DONTENUM ; 
 int /*<<< orphan*/  S_fromCharCode ; 
 int /*<<< orphan*/  Sp_charAt ; 
 int /*<<< orphan*/  Sp_charCodeAt ; 
 int /*<<< orphan*/  Sp_concat ; 
 int /*<<< orphan*/  Sp_indexOf ; 
 int /*<<< orphan*/  Sp_lastIndexOf ; 
 int /*<<< orphan*/  Sp_localeCompare ; 
 int /*<<< orphan*/  Sp_match ; 
 int /*<<< orphan*/  Sp_replace ; 
 int /*<<< orphan*/  Sp_search ; 
 int /*<<< orphan*/  Sp_slice ; 
 int /*<<< orphan*/  Sp_split ; 
 int /*<<< orphan*/  Sp_substring ; 
 int /*<<< orphan*/  Sp_toLowerCase ; 
 int /*<<< orphan*/  Sp_toString ; 
 int /*<<< orphan*/  Sp_toUpperCase ; 
 int /*<<< orphan*/  Sp_trim ; 
 int /*<<< orphan*/  Sp_valueOf ; 
 int /*<<< orphan*/  jsB_String ; 
 int /*<<< orphan*/  jsB_new_String ; 
 int /*<<< orphan*/  jsB_propf (TYPE_3__*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  js_defglobal (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_newcconstructor (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pushobject (TYPE_3__*,TYPE_5__*) ; 

void jsB_initstring(js_State *J)
{
	J->String_prototype->u.s.string = "";
	J->String_prototype->u.s.length = 0;

	js_pushobject(J, J->String_prototype);
	{
		jsB_propf(J, "String.prototype.toString", Sp_toString, 0);
		jsB_propf(J, "String.prototype.valueOf", Sp_valueOf, 0);
		jsB_propf(J, "String.prototype.charAt", Sp_charAt, 1);
		jsB_propf(J, "String.prototype.charCodeAt", Sp_charCodeAt, 1);
		jsB_propf(J, "String.prototype.concat", Sp_concat, 0); /* 1 */
		jsB_propf(J, "String.prototype.indexOf", Sp_indexOf, 1);
		jsB_propf(J, "String.prototype.lastIndexOf", Sp_lastIndexOf, 1);
		jsB_propf(J, "String.prototype.localeCompare", Sp_localeCompare, 1);
		jsB_propf(J, "String.prototype.match", Sp_match, 1);
		jsB_propf(J, "String.prototype.replace", Sp_replace, 2);
		jsB_propf(J, "String.prototype.search", Sp_search, 1);
		jsB_propf(J, "String.prototype.slice", Sp_slice, 2);
		jsB_propf(J, "String.prototype.split", Sp_split, 2);
		jsB_propf(J, "String.prototype.substring", Sp_substring, 2);
		jsB_propf(J, "String.prototype.toLowerCase", Sp_toLowerCase, 0);
		jsB_propf(J, "String.prototype.toLocaleLowerCase", Sp_toLowerCase, 0);
		jsB_propf(J, "String.prototype.toUpperCase", Sp_toUpperCase, 0);
		jsB_propf(J, "String.prototype.toLocaleUpperCase", Sp_toUpperCase, 0);

		/* ES5 */
		jsB_propf(J, "String.prototype.trim", Sp_trim, 0);
	}
	js_newcconstructor(J, jsB_String, jsB_new_String, "String", 0); /* 1 */
	{
		jsB_propf(J, "String.fromCharCode", S_fromCharCode, 0); /* 1 */
	}
	js_defglobal(J, "String", JS_DONTENUM);
}