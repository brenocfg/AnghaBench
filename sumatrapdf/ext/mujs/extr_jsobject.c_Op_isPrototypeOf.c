#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_3__ {struct TYPE_3__* prototype; } ;
typedef  TYPE_1__ js_Object ;

/* Variables and functions */
 scalar_t__ js_isobject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushboolean (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* js_toobject (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void Op_isPrototypeOf(js_State *J)
{
	js_Object *self = js_toobject(J, 0);
	if (js_isobject(J, 1)) {
		js_Object *V = js_toobject(J, 1);
		do {
			V = V->prototype;
			if (V == self) {
				js_pushboolean(J, 1);
				return;
			}
		} while (V);
	}
	js_pushboolean(J, 0);
}