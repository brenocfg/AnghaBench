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
struct TYPE_2__ {int /*<<< orphan*/  extensible; } ;

/* Variables and functions */
 int /*<<< orphan*/  js_isobject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* js_toobject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_typeerror (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void O_isExtensible(js_State *J)
{
	if (!js_isobject(J, 1))
		js_typeerror(J, "not an object");
	js_pushboolean(J, js_toobject(J, 1)->extensible);
}