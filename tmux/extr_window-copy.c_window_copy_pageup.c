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
struct window_pane {int /*<<< orphan*/  modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  window_copy_pageup1 (int /*<<< orphan*/ ,int) ; 

void
window_copy_pageup(struct window_pane *wp, int half_page)
{
	window_copy_pageup1(TAILQ_FIRST(&wp->modes), half_page);
}