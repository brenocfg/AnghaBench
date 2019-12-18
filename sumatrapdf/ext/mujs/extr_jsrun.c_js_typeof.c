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
struct TYPE_6__ {TYPE_1__* object; } ;
struct TYPE_7__ {int type; TYPE_2__ u; } ;
typedef  TYPE_3__ js_Value ;
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  JS_CCFUNCTION ; 
 int /*<<< orphan*/  JS_CFUNCTION ; 
#define  JS_TBOOLEAN 135 
#define  JS_TLITSTR 134 
#define  JS_TMEMSTR 133 
#define  JS_TNULL 132 
#define  JS_TNUMBER 131 
#define  JS_TOBJECT 130 
#define  JS_TSHRSTR 129 
#define  JS_TUNDEFINED 128 
 TYPE_3__* stackidx (int /*<<< orphan*/ *,int) ; 

const char *js_typeof(js_State *J, int idx)
{
	js_Value *v = stackidx(J, idx);
	switch (v->type) {
	default:
	case JS_TSHRSTR: return "string";
	case JS_TUNDEFINED: return "undefined";
	case JS_TNULL: return "object";
	case JS_TBOOLEAN: return "boolean";
	case JS_TNUMBER: return "number";
	case JS_TLITSTR: return "string";
	case JS_TMEMSTR: return "string";
	case JS_TOBJECT:
		if (v->u.object->type == JS_CFUNCTION || v->u.object->type == JS_CCFUNCTION)
			return "function";
		return "object";
	}
}