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
struct TYPE_4__ {scalar_t__ envtop; int /*<<< orphan*/ * E; int /*<<< orphan*/ ** envstack; } ;
typedef  TYPE_1__ js_State ;
typedef  int /*<<< orphan*/  js_Environment ;

/* Variables and functions */
 scalar_t__ JS_ENVLIMIT ; 
 int /*<<< orphan*/  js_stackoverflow (TYPE_1__*) ; 

__attribute__((used)) static void jsR_savescope(js_State *J, js_Environment *newE)
{
	if (J->envtop + 1 >= JS_ENVLIMIT)
		js_stackoverflow(J);
	J->envstack[J->envtop++] = J->E;
	J->E = newE;
}