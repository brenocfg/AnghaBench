#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_4__* Number_prototype; } ;
typedef  TYPE_2__ js_State ;
struct TYPE_10__ {scalar_t__ number; } ;
struct TYPE_12__ {TYPE_1__ u; } ;

/* Variables and functions */
 int INFINITY ; 
 int /*<<< orphan*/  JS_DONTENUM ; 
 int NAN ; 
 int /*<<< orphan*/  Np_toExponential ; 
 int /*<<< orphan*/  Np_toFixed ; 
 int /*<<< orphan*/  Np_toPrecision ; 
 int /*<<< orphan*/  Np_toString ; 
 int /*<<< orphan*/  Np_valueOf ; 
 int /*<<< orphan*/  jsB_Number ; 
 int /*<<< orphan*/  jsB_new_Number ; 
 int /*<<< orphan*/  jsB_propf (TYPE_2__*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jsB_propn (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  js_defglobal (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_newcconstructor (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pushobject (TYPE_2__*,TYPE_4__*) ; 

void jsB_initnumber(js_State *J)
{
	J->Number_prototype->u.number = 0;

	js_pushobject(J, J->Number_prototype);
	{
		jsB_propf(J, "Number.prototype.valueOf", Np_valueOf, 0);
		jsB_propf(J, "Number.prototype.toString", Np_toString, 1);
		jsB_propf(J, "Number.prototype.toLocaleString", Np_toString, 0);
		jsB_propf(J, "Number.prototype.toFixed", Np_toFixed, 1);
		jsB_propf(J, "Number.prototype.toExponential", Np_toExponential, 1);
		jsB_propf(J, "Number.prototype.toPrecision", Np_toPrecision, 1);
	}
	js_newcconstructor(J, jsB_Number, jsB_new_Number, "Number", 0); /* 1 */
	{
		jsB_propn(J, "MAX_VALUE", 1.7976931348623157e+308);
		jsB_propn(J, "MIN_VALUE", 5e-324);
		jsB_propn(J, "NaN", NAN);
		jsB_propn(J, "NEGATIVE_INFINITY", -INFINITY);
		jsB_propn(J, "POSITIVE_INFINITY", INFINITY);
	}
	js_defglobal(J, "Number", JS_DONTENUM);
}