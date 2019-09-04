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
 int /*<<< orphan*/  ERROR ; 
#define  EXTENSION_STATE_CREATED 131 
#define  EXTENSION_STATE_NOT_INSTALLED 130 
#define  EXTENSION_STATE_TRANSITIONING 129 
#define  EXTENSION_STATE_UNKNOWN 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  extension_update_state () ; 
 int extstate ; 
 scalar_t__ ts_guc_restoring ; 

bool
ts_extension_is_loaded(void)
{
	/* when restoring deactivate extension */
	if (ts_guc_restoring)
		return false;

	if (EXTENSION_STATE_UNKNOWN == extstate || EXTENSION_STATE_TRANSITIONING == extstate)
	{
		/* status may have updated without a relcache invalidate event */
		extension_update_state();
	}

	switch (extstate)
	{
		case EXTENSION_STATE_CREATED:
			return true;
		case EXTENSION_STATE_NOT_INSTALLED:
		case EXTENSION_STATE_UNKNOWN:
		case EXTENSION_STATE_TRANSITIONING:

			/*
			 * Turn off extension during upgrade scripts. This is necessary so
			 * that, for example, the catalog does not go looking for things
			 * that aren't yet there.
			 */
			return false;
		default:
			elog(ERROR, "unknown state: %d", extstate);
			return false;
	}
}