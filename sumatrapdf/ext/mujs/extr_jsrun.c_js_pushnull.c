#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSTACK (int) ; 
 int /*<<< orphan*/  JS_TNULL ; 
 TYPE_1__* STACK ; 
 size_t TOP ; 

void js_pushnull(js_State *J)
{
	CHECKSTACK(1);
	STACK[TOP].type = JS_TNULL;
	++TOP;
}