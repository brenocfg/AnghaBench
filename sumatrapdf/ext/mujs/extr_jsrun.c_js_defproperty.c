#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;

/* Variables and functions */
 int /*<<< orphan*/  jsR_defproperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_toobject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stackidx (int /*<<< orphan*/ *,int) ; 

void js_defproperty(js_State *J, int idx, const char *name, int atts)
{
	jsR_defproperty(J, js_toobject(J, idx), name, atts, stackidx(J, -1), NULL, NULL);
	js_pop(J, 1);
}