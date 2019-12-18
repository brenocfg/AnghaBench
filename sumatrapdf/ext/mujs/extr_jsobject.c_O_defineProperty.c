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
 int /*<<< orphan*/  ToPropertyDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_copy (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_isobject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_toobject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_typeerror (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void O_defineProperty(js_State *J)
{
	if (!js_isobject(J, 1)) js_typeerror(J, "not an object");
	if (!js_isobject(J, 3)) js_typeerror(J, "not an object");
	ToPropertyDescriptor(J, js_toobject(J, 1), js_tostring(J, 2), js_toobject(J, 3));
	js_copy(J, 1);
}