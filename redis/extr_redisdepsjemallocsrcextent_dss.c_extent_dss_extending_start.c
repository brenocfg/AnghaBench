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
typedef  int /*<<< orphan*/  spin_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_ACQ_REL ; 
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 int /*<<< orphan*/  SPIN_INITIALIZER ; 
 scalar_t__ atomic_compare_exchange_weak_b (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dss_extending ; 
 int /*<<< orphan*/  spin_adaptive (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
extent_dss_extending_start(void) {
	spin_t spinner = SPIN_INITIALIZER;
	while (true) {
		bool expected = false;
		if (atomic_compare_exchange_weak_b(&dss_extending, &expected,
		    true, ATOMIC_ACQ_REL, ATOMIC_RELAXED)) {
			break;
		}
		spin_adaptive(&spinner);
	}
}