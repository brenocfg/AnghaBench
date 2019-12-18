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
struct TYPE_4__ {int /*<<< orphan*/  number; } ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__ u; } ;
typedef  TYPE_2__ js_Object ;

/* Variables and functions */
 scalar_t__ JS_CDATE ; 
 int /*<<< orphan*/  TimeClip (double) ; 
 int /*<<< orphan*/  js_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* js_toobject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_typeerror (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void js_setdate(js_State *J, int idx, double t)
{
	js_Object *self = js_toobject(J, idx);
	if (self->type != JS_CDATE)
		js_typeerror(J, "not a date");
	self->u.number = TimeClip(t);
	js_pushnumber(J, self->u.number);
}