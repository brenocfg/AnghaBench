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
struct TYPE_3__ {scalar_t__ chapter; scalar_t__ page; } ;
typedef  TYPE_1__ fz_location ;

/* Variables and functions */
 int /*<<< orphan*/  js_newarray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pushnumber (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  js_setindex (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void push_location(js_State *J, fz_location loc)
{
	if (loc.chapter == 0)
		js_pushnumber(J, loc.page+1);
	else
	{
		js_newarray(J);
		js_pushnumber(J, loc.chapter+1);
		js_setindex(J, -2, 0);
		js_pushnumber(J, loc.page+1);
		js_setindex(J, -2, 1);
	}
}