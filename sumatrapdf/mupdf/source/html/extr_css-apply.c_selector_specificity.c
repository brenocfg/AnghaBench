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
typedef  int /*<<< orphan*/  fz_css_selector ;

/* Variables and functions */
 int count_selector_atts (int /*<<< orphan*/ *) ; 
 int count_selector_ids (int /*<<< orphan*/ *) ; 
 int count_selector_names (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
selector_specificity(fz_css_selector *sel, int important)
{
	int b = count_selector_ids(sel);
	int c = count_selector_atts(sel);
	int d = count_selector_names(sel);
	return important * 1000 + b * 100 + c * 10 + d;
}