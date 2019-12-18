#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_3__ {char* litstr; } ;
struct TYPE_4__ {TYPE_1__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  JS_TLITSTR ; 
 TYPE_2__* STACK ; 
 size_t TOP ; 
 int /*<<< orphan*/  js_throw (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void js_stackoverflow(js_State *J)
{
	STACK[TOP].type = JS_TLITSTR;
	STACK[TOP].u.litstr = "stack overflow";
	++TOP;
	js_throw(J);
}