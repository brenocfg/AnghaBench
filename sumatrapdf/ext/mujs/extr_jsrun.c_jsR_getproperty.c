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
typedef  int /*<<< orphan*/  js_Object ;

/* Variables and functions */
 int /*<<< orphan*/  jsR_hasproperty (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  js_pushundefined (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void jsR_getproperty(js_State *J, js_Object *obj, const char *name)
{
	if (!jsR_hasproperty(J, obj, name))
		js_pushundefined(J);
}