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
 int /*<<< orphan*/  redact_snaps_contains (scalar_t__ const*,scalar_t__,scalar_t__ const) ; 

__attribute__((used)) static boolean_t
redact_snaps_equal(const uint64_t *snaps1, uint64_t num_snaps1,
    const uint64_t *snaps2, uint64_t num_snaps2)
{
	if (num_snaps1 != num_snaps2)
		return (B_FALSE);
	for (int i = 0; i < num_snaps1; i++) {
		if (!redact_snaps_contains(snaps2, num_snaps2, snaps1[i]))
			return (B_FALSE);
	}
	return (B_TRUE);
}