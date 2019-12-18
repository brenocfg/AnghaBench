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
typedef  int /*<<< orphan*/  fz_css_value ;
typedef  int /*<<< orphan*/  fz_css_match ;

/* Variables and functions */
 int /*<<< orphan*/  add_shorthand_trbl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*,char*,char*,char*) ; 

__attribute__((used)) static void
add_shorthand_margin(fz_css_match *match, fz_css_value *value, int spec)
{
	add_shorthand_trbl(match, value, spec,
		"margin-top", "margin-right", "margin-bottom", "margin-left");
}