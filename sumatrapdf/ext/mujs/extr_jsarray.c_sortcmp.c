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
struct TYPE_3__ {scalar_t__ type; } ;
struct sortslot {int /*<<< orphan*/ * J; TYPE_1__ v; } ;
typedef  TYPE_1__ js_Value ;
typedef  int /*<<< orphan*/  js_State ;

/* Variables and functions */
 scalar_t__ JS_TUNDEFINED ; 
 int /*<<< orphan*/  js_call (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_copy (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_iscallable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushundefined (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pushvalue (int /*<<< orphan*/ *,TYPE_1__ const) ; 
 int js_tonumber (int /*<<< orphan*/ *,int) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 int strcmp (char const*,char const*) ; 

__attribute__((used)) static int sortcmp(const void *avoid, const void *bvoid)
{
	const struct sortslot *aslot = avoid, *bslot = bvoid;
	const js_Value *a = &aslot->v, *b = &bslot->v;
	js_State *J = aslot->J;
	const char *sx, *sy;
	int c;

	int unx = (a->type == JS_TUNDEFINED);
	int uny = (b->type == JS_TUNDEFINED);
	if (unx) return !uny;
	if (uny) return -1;

	if (js_iscallable(J, 1)) {
		js_copy(J, 1); /* copy function */
		js_pushundefined(J);
		js_pushvalue(J, *a);
		js_pushvalue(J, *b);
		js_call(J, 2);
		c = js_tonumber(J, -1);
		js_pop(J, 1);
	} else {
		js_pushvalue(J, *a);
		js_pushvalue(J, *b);
		sx = js_tostring(J, -2);
		sy = js_tostring(J, -1);
		c = strcmp(sx, sy);
		js_pop(J, 2);
	}
	return c;
}