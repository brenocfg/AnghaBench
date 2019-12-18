#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_4__ {double number; } ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__ u; } ;
typedef  TYPE_2__ js_Object ;

/* Variables and functions */
 scalar_t__ JS_CNUMBER ; 
 scalar_t__ isinf (double) ; 
 scalar_t__ isnan (double) ; 
 int /*<<< orphan*/  jsV_numbertostring (int /*<<< orphan*/ *,char*,double) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_rangeerror (int /*<<< orphan*/ *,char*,int) ; 
 int js_tointeger (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* js_toobject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_typeerror (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  numtostr (int /*<<< orphan*/ *,char*,int,double) ; 

__attribute__((used)) static void Np_toExponential(js_State *J)
{
	js_Object *self = js_toobject(J, 0);
	int width = js_tointeger(J, 1);
	char buf[32];
	double x;
	if (self->type != JS_CNUMBER) js_typeerror(J, "not a number");
	if (width < 0) js_rangeerror(J, "precision %d out of range", width);
	if (width > 20) js_rangeerror(J, "precision %d out of range", width);
	x = self->u.number;
	if (isnan(x) || isinf(x))
		js_pushstring(J, jsV_numbertostring(J, buf, x));
	else
		numtostr(J, "%.*e", width, self->u.number);
}