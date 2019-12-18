#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  report; } ;
typedef  TYPE_1__ js_State ;
typedef  int /*<<< orphan*/  js_Report ;

/* Variables and functions */

void js_setreport(js_State *J, js_Report report)
{
	J->report = report;
}