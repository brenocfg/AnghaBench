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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  redact_snaps_contains (scalar_t__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static boolean_t
compatible_redact_snaps(uint64_t *origin_snaps, uint64_t origin_num_snaps,
    uint64_t *redact_snaps, uint64_t num_redact_snaps)
{
	/*
	 * Short circuit the comparison; if we are redacted with respect to
	 * more snapshots than the origin, we can't be redacted with respect
	 * to a subset.
	 */
	if (num_redact_snaps > origin_num_snaps) {
		return (B_FALSE);
	}

	for (int i = 0; i < num_redact_snaps; i++) {
		if (!redact_snaps_contains(origin_snaps, origin_num_snaps,
		    redact_snaps[i])) {
			return (B_FALSE);
		}
	}
	return (B_TRUE);
}