#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/ * Error_prototype; void* URIError_prototype; void* TypeError_prototype; void* SyntaxError_prototype; void* ReferenceError_prototype; void* RangeError_prototype; void* EvalError_prototype; int /*<<< orphan*/ * Object_prototype; void* Date_prototype; void* RegExp_prototype; void* String_prototype; void* Number_prototype; void* Boolean_prototype; void* Function_prototype; void* Array_prototype; } ;
typedef  TYPE_1__ js_State ;

/* Variables and functions */
 int /*<<< orphan*/  INFINITY ; 
 int /*<<< orphan*/  JS_CARRAY ; 
 int /*<<< orphan*/  JS_CBOOLEAN ; 
 int /*<<< orphan*/  JS_CCFUNCTION ; 
 int /*<<< orphan*/  JS_CDATE ; 
 int /*<<< orphan*/  JS_CERROR ; 
 int /*<<< orphan*/  JS_CNUMBER ; 
 int /*<<< orphan*/  JS_COBJECT ; 
 int /*<<< orphan*/  JS_CSTRING ; 
 int JS_DONTCONF ; 
 int JS_DONTENUM ; 
 int JS_READONLY ; 
 int /*<<< orphan*/  NAN ; 
 int /*<<< orphan*/  jsB_decodeURI ; 
 int /*<<< orphan*/  jsB_decodeURIComponent ; 
 int /*<<< orphan*/  jsB_encodeURI ; 
 int /*<<< orphan*/  jsB_encodeURIComponent ; 
 int /*<<< orphan*/  jsB_globalf (TYPE_1__*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jsB_initarray (TYPE_1__*) ; 
 int /*<<< orphan*/  jsB_initboolean (TYPE_1__*) ; 
 int /*<<< orphan*/  jsB_initdate (TYPE_1__*) ; 
 int /*<<< orphan*/  jsB_initerror (TYPE_1__*) ; 
 int /*<<< orphan*/  jsB_initfunction (TYPE_1__*) ; 
 int /*<<< orphan*/  jsB_initjson (TYPE_1__*) ; 
 int /*<<< orphan*/  jsB_initmath (TYPE_1__*) ; 
 int /*<<< orphan*/  jsB_initnumber (TYPE_1__*) ; 
 int /*<<< orphan*/  jsB_initobject (TYPE_1__*) ; 
 int /*<<< orphan*/  jsB_initregexp (TYPE_1__*) ; 
 int /*<<< orphan*/  jsB_initstring (TYPE_1__*) ; 
 int /*<<< orphan*/  jsB_isFinite ; 
 int /*<<< orphan*/  jsB_isNaN ; 
 int /*<<< orphan*/  jsB_parseFloat ; 
 int /*<<< orphan*/  jsB_parseInt ; 
 void* jsV_newobject (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_defglobal (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  js_pushnumber (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pushundefined (TYPE_1__*) ; 

void jsB_init(js_State *J)
{
	/* Create the prototype objects here, before the constructors */
	J->Object_prototype = jsV_newobject(J, JS_COBJECT, NULL);
	J->Array_prototype = jsV_newobject(J, JS_CARRAY, J->Object_prototype);
	J->Function_prototype = jsV_newobject(J, JS_CCFUNCTION, J->Object_prototype);
	J->Boolean_prototype = jsV_newobject(J, JS_CBOOLEAN, J->Object_prototype);
	J->Number_prototype = jsV_newobject(J, JS_CNUMBER, J->Object_prototype);
	J->String_prototype = jsV_newobject(J, JS_CSTRING, J->Object_prototype);
	J->RegExp_prototype = jsV_newobject(J, JS_COBJECT, J->Object_prototype);
	J->Date_prototype = jsV_newobject(J, JS_CDATE, J->Object_prototype);

	/* All the native error types */
	J->Error_prototype = jsV_newobject(J, JS_CERROR, J->Object_prototype);
	J->EvalError_prototype = jsV_newobject(J, JS_CERROR, J->Error_prototype);
	J->RangeError_prototype = jsV_newobject(J, JS_CERROR, J->Error_prototype);
	J->ReferenceError_prototype = jsV_newobject(J, JS_CERROR, J->Error_prototype);
	J->SyntaxError_prototype = jsV_newobject(J, JS_CERROR, J->Error_prototype);
	J->TypeError_prototype = jsV_newobject(J, JS_CERROR, J->Error_prototype);
	J->URIError_prototype = jsV_newobject(J, JS_CERROR, J->Error_prototype);

	/* Create the constructors and fill out the prototype objects */
	jsB_initobject(J);
	jsB_initarray(J);
	jsB_initfunction(J);
	jsB_initboolean(J);
	jsB_initnumber(J);
	jsB_initstring(J);
	jsB_initregexp(J);
	jsB_initdate(J);
	jsB_initerror(J);
	jsB_initmath(J);
	jsB_initjson(J);

	/* Initialize the global object */
	js_pushnumber(J, NAN);
	js_defglobal(J, "NaN", JS_READONLY | JS_DONTENUM | JS_DONTCONF);

	js_pushnumber(J, INFINITY);
	js_defglobal(J, "Infinity", JS_READONLY | JS_DONTENUM | JS_DONTCONF);

	js_pushundefined(J);
	js_defglobal(J, "undefined", JS_READONLY | JS_DONTENUM | JS_DONTCONF);

	jsB_globalf(J, "parseInt", jsB_parseInt, 1);
	jsB_globalf(J, "parseFloat", jsB_parseFloat, 1);
	jsB_globalf(J, "isNaN", jsB_isNaN, 1);
	jsB_globalf(J, "isFinite", jsB_isFinite, 1);

	jsB_globalf(J, "decodeURI", jsB_decodeURI, 1);
	jsB_globalf(J, "decodeURIComponent", jsB_decodeURIComponent, 1);
	jsB_globalf(J, "encodeURI", jsB_encodeURI, 1);
	jsB_globalf(J, "encodeURIComponent", jsB_encodeURIComponent, 1);
}