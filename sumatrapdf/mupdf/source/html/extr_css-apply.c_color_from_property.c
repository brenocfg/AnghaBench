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
typedef  int /*<<< orphan*/  fz_css_match ;
typedef  int /*<<< orphan*/  fz_css_color ;

/* Variables and functions */
 int /*<<< orphan*/  color_from_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value_from_property (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static fz_css_color
color_from_property(fz_css_match *match, const char *property, fz_css_color initial)
{
	return color_from_value(value_from_property(match, property), initial);
}