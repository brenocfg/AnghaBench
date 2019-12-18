#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* E; } ;
typedef  TYPE_2__ js_State ;
struct TYPE_6__ {int /*<<< orphan*/  variables; } ;

/* Variables and functions */
 int JS_DONTCONF ; 
 int JS_DONTENUM ; 
 int /*<<< orphan*/  jsR_defproperty (TYPE_2__*,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stackidx (TYPE_2__*,int) ; 

__attribute__((used)) static void js_initvar(js_State *J, const char *name, int idx)
{
	jsR_defproperty(J, J->E->variables, name, JS_DONTENUM | JS_DONTCONF, stackidx(J, idx), NULL, NULL);
}