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
typedef  int /*<<< orphan*/  nstime_t ;

/* Variables and functions */
 scalar_t__ monotonic_mock ; 
 int /*<<< orphan*/  nstime_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nupdates_mock ; 
 int /*<<< orphan*/  time_mock ; 

__attribute__((used)) static bool
nstime_update_mock(nstime_t *time) {
	nupdates_mock++;
	if (monotonic_mock) {
		nstime_copy(time, &time_mock);
	}
	return !monotonic_mock;
}