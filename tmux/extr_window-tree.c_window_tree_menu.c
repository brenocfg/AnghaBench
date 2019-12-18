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
struct window_tree_modedata {struct window_pane* wp; } ;
struct window_pane {int /*<<< orphan*/  modes; } ;
struct window_mode_entry {void* data; } ;
struct client {int dummy; } ;
typedef  int /*<<< orphan*/  key_code ;

/* Variables and functions */
 struct window_mode_entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  window_tree_key (struct window_mode_entry*,struct client*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
window_tree_menu(void *modedata, struct client *c, key_code key)
{
	struct window_tree_modedata	*data = modedata;
	struct window_pane		*wp = data->wp;
	struct window_mode_entry	*wme;

	wme = TAILQ_FIRST(&wp->modes);
	if (wme == NULL || wme->data != modedata)
		return;
	window_tree_key(wme, c, NULL, NULL, key, NULL);
}