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
typedef  int /*<<< orphan*/  UnitActiveState ;

/* Variables and functions */
 int IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNIT_DEACTIVATING ; 
 int /*<<< orphan*/  UNIT_FAILED ; 
 int /*<<< orphan*/  UNIT_INACTIVE ; 

__attribute__((used)) static inline bool UNIT_IS_INACTIVE_OR_DEACTIVATING(UnitActiveState t) {
        return IN_SET(t, UNIT_INACTIVE, UNIT_FAILED, UNIT_DEACTIVATING);
}