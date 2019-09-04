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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ embedded_loc_filename ; 
 int /*<<< orphan*/  free_dialog_list () ; 
 int /*<<< orphan*/  free_locale_list () ; 
 int /*<<< orphan*/  htab_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htab_loc ; 
 scalar_t__ loc_filename ; 
 int /*<<< orphan*/  localization_initialized ; 
 int /*<<< orphan*/  mtab_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_free (scalar_t__) ; 

void _exit_localization(BOOL reinit) {
	if (!localization_initialized)
		return;
	if (!reinit) {
		free_locale_list();
		if (loc_filename != embedded_loc_filename)
			safe_free(loc_filename);
	}
	free_dialog_list();
	mtab_destroy(reinit);
	htab_destroy(&htab_loc);
}