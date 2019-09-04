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
struct window_pane {TYPE_1__* window; } ;
struct window_mode_entry {struct window_pane* wp; } ;
struct TYPE_2__ {int /*<<< orphan*/  options; } ;

/* Variables and functions */
 scalar_t__ MODEKEY_VI ; 
 scalar_t__ options_get_number (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static const char *
window_copy_key_table(struct window_mode_entry *wme)
{
	struct window_pane	*wp = wme->wp;

	if (options_get_number(wp->window->options, "mode-keys") == MODEKEY_VI)
		return ("copy-mode-vi");
	return ("copy-mode");
}