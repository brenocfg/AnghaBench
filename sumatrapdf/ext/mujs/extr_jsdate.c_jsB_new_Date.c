#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  Date_prototype; } ;
typedef  TYPE_2__ js_State ;
struct TYPE_15__ {double number; } ;
struct TYPE_17__ {TYPE_1__ u; } ;
typedef  TYPE_3__ js_Object ;

/* Variables and functions */
 int /*<<< orphan*/  JS_CDATE ; 
 int /*<<< orphan*/  JS_HNONE ; 
 double MakeDate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MakeDay (double,double,double) ; 
 int /*<<< orphan*/  MakeTime (double,double,double,double) ; 
 double Now () ; 
 double TimeClip (double) ; 
 double UTC (double) ; 
 TYPE_3__* jsV_newobject (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int js_gettop (TYPE_2__*) ; 
 scalar_t__ js_isstring (TYPE_2__*,int) ; 
 double js_optnumber (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  js_pushobject (TYPE_2__*,TYPE_3__*) ; 
 double js_tonumber (TYPE_2__*,int) ; 
 int /*<<< orphan*/  js_toprimitive (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_tostring (TYPE_2__*,int) ; 
 double parseDateTime (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jsB_new_Date(js_State *J)
{
	int top = js_gettop(J);
	js_Object *obj;
	double t;

	if (top == 1)
		t = Now();
	else if (top == 2) {
		js_toprimitive(J, 1, JS_HNONE);
		if (js_isstring(J, 1))
			t = parseDateTime(js_tostring(J, 1));
		else
			t = TimeClip(js_tonumber(J, 1));
	} else {
		double y, m, d, H, M, S, ms;
		y = js_tonumber(J, 1);
		if (y < 100) y += 1900;
		m = js_tonumber(J, 2);
		d = js_optnumber(J, 3, 1);
		H = js_optnumber(J, 4, 0);
		M = js_optnumber(J, 5, 0);
		S = js_optnumber(J, 6, 0);
		ms = js_optnumber(J, 7, 0);
		t = MakeDate(MakeDay(y, m, d), MakeTime(H, M, S, ms));
		t = TimeClip(UTC(t));
	}

	obj = jsV_newobject(J, JS_CDATE, J->Date_prototype);
	obj->u.number = t;

	js_pushobject(J, obj);
}