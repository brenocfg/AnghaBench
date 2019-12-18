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

/* Variables and functions */
 int /*<<< orphan*/  currentrotate ; 
 int /*<<< orphan*/  currentzoom ; 
 int /*<<< orphan*/  draw_page_bounds ; 
 int /*<<< orphan*/  draw_page_ctm ; 
 int /*<<< orphan*/  fz_transform_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_transform_rect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_bounds ; 

void transform_page(void)
{
	draw_page_ctm = fz_transform_page(page_bounds, currentzoom, currentrotate);
	draw_page_bounds = fz_transform_rect(page_bounds, draw_page_ctm);
}