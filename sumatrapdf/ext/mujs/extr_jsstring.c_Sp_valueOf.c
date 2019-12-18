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
struct TYPE_5__ {int /*<<< orphan*/  string; } ;
struct TYPE_6__ {TYPE_1__ s; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_2__ u; } ;
typedef  TYPE_3__ js_Object ;

/* Variables and functions */
 scalar_t__ JS_CSTRING ; 
 int /*<<< orphan*/  js_pushliteral (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* js_toobject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_typeerror (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void Sp_valueOf(js_State *J)
{
	js_Object *self = js_toobject(J, 0);
	if (self->type != JS_CSTRING) js_typeerror(J, "not a string");
	js_pushliteral(J, self->u.s.string);
}