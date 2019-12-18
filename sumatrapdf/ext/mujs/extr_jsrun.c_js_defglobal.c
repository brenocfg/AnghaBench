#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  G; } ;
typedef  TYPE_1__ js_State ;

/* Variables and functions */
 int /*<<< orphan*/  jsR_defproperty (TYPE_1__*,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pop (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stackidx (TYPE_1__*,int) ; 

void js_defglobal(js_State *J, const char *name, int atts)
{
	jsR_defproperty(J, J->G, name, atts, stackidx(J, -1), NULL, NULL);
	js_pop(J, 1);
}