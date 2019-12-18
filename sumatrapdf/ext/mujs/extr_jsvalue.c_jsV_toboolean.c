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
struct TYPE_6__ {int boolean; TYPE_1__* memstr; int /*<<< orphan*/ * litstr; int /*<<< orphan*/  number; int /*<<< orphan*/ * shrstr; } ;
struct TYPE_7__ {int type; TYPE_2__ u; } ;
typedef  TYPE_3__ js_Value ;
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_5__ {int /*<<< orphan*/ * p; } ;

/* Variables and functions */
#define  JS_TBOOLEAN 135 
#define  JS_TLITSTR 134 
#define  JS_TMEMSTR 133 
#define  JS_TNULL 132 
#define  JS_TNUMBER 131 
#define  JS_TOBJECT 130 
#define  JS_TSHRSTR 129 
#define  JS_TUNDEFINED 128 
 int /*<<< orphan*/  isnan (int /*<<< orphan*/ ) ; 

int jsV_toboolean(js_State *J, js_Value *v)
{
	switch (v->type) {
	default:
	case JS_TSHRSTR: return v->u.shrstr[0] != 0;
	case JS_TUNDEFINED: return 0;
	case JS_TNULL: return 0;
	case JS_TBOOLEAN: return v->u.boolean;
	case JS_TNUMBER: return v->u.number != 0 && !isnan(v->u.number);
	case JS_TLITSTR: return v->u.litstr[0] != 0;
	case JS_TMEMSTR: return v->u.memstr->p[0] != 0;
	case JS_TOBJECT: return 1;
	}
}