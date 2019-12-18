#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_4__ {void* page; void* chapter; } ;
typedef  TYPE_1__ fz_location ;

/* Variables and functions */
 TYPE_1__ fz_make_location (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  js_getindex (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ js_isnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 void* js_tryinteger (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static fz_location try_location(js_State *J)
{
	fz_location loc;
	if (js_isnumber(J, -1))
		loc = fz_make_location(0, js_tryinteger(J, -1, 1) - 1);
	else
	{
		js_getindex(J, -1, 0);
		loc.chapter = js_tryinteger(J, -1, 1) - 1;
		js_pop(J, 1);
		js_getindex(J, -1, 1);
		loc.page = js_tryinteger(J, -1, 1) - 1;
		js_pop(J, 1);
	}
	return loc;
}