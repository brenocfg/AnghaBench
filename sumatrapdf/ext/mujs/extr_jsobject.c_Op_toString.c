#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_5__ {char* tag; } ;
struct TYPE_6__ {TYPE_1__ user; } ;
struct TYPE_7__ {int type; TYPE_2__ u; } ;
typedef  TYPE_3__ js_Object ;

/* Variables and functions */
#define  JS_CARGUMENTS 143 
#define  JS_CARRAY 142 
#define  JS_CBOOLEAN 141 
#define  JS_CCFUNCTION 140 
#define  JS_CDATE 139 
#define  JS_CERROR 138 
#define  JS_CFUNCTION 137 
#define  JS_CITERATOR 136 
#define  JS_CJSON 135 
#define  JS_CMATH 134 
#define  JS_CNUMBER 133 
#define  JS_COBJECT 132 
#define  JS_CREGEXP 131 
#define  JS_CSCRIPT 130 
#define  JS_CSTRING 129 
#define  JS_CUSERDATA 128 
 int /*<<< orphan*/  js_concat (int /*<<< orphan*/ *) ; 
 scalar_t__ js_isnull (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ js_isundefined (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pushliteral (int /*<<< orphan*/ *,char*) ; 
 TYPE_3__* js_toobject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Op_toString(js_State *J)
{
	if (js_isundefined(J, 0))
		js_pushliteral(J, "[object Undefined]");
	else if (js_isnull(J, 0))
		js_pushliteral(J, "[object Null]");
	else {
		js_Object *self = js_toobject(J, 0);
		switch (self->type) {
		case JS_COBJECT: js_pushliteral(J, "[object Object]"); break;
		case JS_CARRAY: js_pushliteral(J, "[object Array]"); break;
		case JS_CFUNCTION: js_pushliteral(J, "[object Function]"); break;
		case JS_CSCRIPT: js_pushliteral(J, "[object Function]"); break;
		case JS_CCFUNCTION: js_pushliteral(J, "[object Function]"); break;
		case JS_CERROR: js_pushliteral(J, "[object Error]"); break;
		case JS_CBOOLEAN: js_pushliteral(J, "[object Boolean]"); break;
		case JS_CNUMBER: js_pushliteral(J, "[object Number]"); break;
		case JS_CSTRING: js_pushliteral(J, "[object String]"); break;
		case JS_CREGEXP: js_pushliteral(J, "[object RegExp]"); break;
		case JS_CDATE: js_pushliteral(J, "[object Date]"); break;
		case JS_CMATH: js_pushliteral(J, "[object Math]"); break;
		case JS_CJSON: js_pushliteral(J, "[object JSON]"); break;
		case JS_CARGUMENTS: js_pushliteral(J, "[object Arguments]"); break;
		case JS_CITERATOR: js_pushliteral(J, "[Iterator]"); break;
		case JS_CUSERDATA:
			js_pushliteral(J, "[object ");
			js_pushliteral(J, self->u.user.tag);
			js_concat(J);
			js_pushliteral(J, "]");
			js_concat(J);
			break;
		}
	}
}