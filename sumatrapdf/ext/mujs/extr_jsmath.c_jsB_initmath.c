#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  Object_prototype; int /*<<< orphan*/  seed; } ;
typedef  TYPE_1__ js_State ;

/* Variables and functions */
 int /*<<< orphan*/  JS_CMATH ; 
 int /*<<< orphan*/  JS_DONTENUM ; 
 int /*<<< orphan*/  Math_abs ; 
 int /*<<< orphan*/  Math_acos ; 
 int /*<<< orphan*/  Math_asin ; 
 int /*<<< orphan*/  Math_atan ; 
 int /*<<< orphan*/  Math_atan2 ; 
 int /*<<< orphan*/  Math_ceil ; 
 int /*<<< orphan*/  Math_cos ; 
 int /*<<< orphan*/  Math_exp ; 
 int /*<<< orphan*/  Math_floor ; 
 int /*<<< orphan*/  Math_log ; 
 int /*<<< orphan*/  Math_max ; 
 int /*<<< orphan*/  Math_min ; 
 int /*<<< orphan*/  Math_pow ; 
 int /*<<< orphan*/  Math_random ; 
 int /*<<< orphan*/  Math_round ; 
 int /*<<< orphan*/  Math_sin ; 
 int /*<<< orphan*/  Math_sqrt ; 
 int /*<<< orphan*/  Math_tan ; 
 int /*<<< orphan*/  jsB_propf (TYPE_1__*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jsB_propn (TYPE_1__*,char*,double) ; 
 int /*<<< orphan*/  jsV_newobject (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_defglobal (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pushobject (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

void jsB_initmath(js_State *J)
{
	J->seed = time(NULL);

	js_pushobject(J, jsV_newobject(J, JS_CMATH, J->Object_prototype));
	{
		jsB_propn(J, "E", 2.7182818284590452354);
		jsB_propn(J, "LN10", 2.302585092994046);
		jsB_propn(J, "LN2", 0.6931471805599453);
		jsB_propn(J, "LOG2E", 1.4426950408889634);
		jsB_propn(J, "LOG10E", 0.4342944819032518);
		jsB_propn(J, "PI", 3.1415926535897932);
		jsB_propn(J, "SQRT1_2", 0.7071067811865476);
		jsB_propn(J, "SQRT2", 1.4142135623730951);

		jsB_propf(J, "Math.abs", Math_abs, 1);
		jsB_propf(J, "Math.acos", Math_acos, 1);
		jsB_propf(J, "Math.asin", Math_asin, 1);
		jsB_propf(J, "Math.atan", Math_atan, 1);
		jsB_propf(J, "Math.atan2", Math_atan2, 2);
		jsB_propf(J, "Math.ceil", Math_ceil, 1);
		jsB_propf(J, "Math.cos", Math_cos, 1);
		jsB_propf(J, "Math.exp", Math_exp, 1);
		jsB_propf(J, "Math.floor", Math_floor, 1);
		jsB_propf(J, "Math.log", Math_log, 1);
		jsB_propf(J, "Math.max", Math_max, 0); /* 2 */
		jsB_propf(J, "Math.min", Math_min, 0); /* 2 */
		jsB_propf(J, "Math.pow", Math_pow, 2);
		jsB_propf(J, "Math.random", Math_random, 0);
		jsB_propf(J, "Math.round", Math_round, 1);
		jsB_propf(J, "Math.sin", Math_sin, 1);
		jsB_propf(J, "Math.sqrt", Math_sqrt, 1);
		jsB_propf(J, "Math.tan", Math_tan, 1);
	}
	js_defglobal(J, "Math", JS_DONTENUM);
}