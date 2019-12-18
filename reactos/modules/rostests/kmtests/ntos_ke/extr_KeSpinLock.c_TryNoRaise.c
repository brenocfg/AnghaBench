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
typedef  int /*<<< orphan*/  PKSPIN_LOCK ;
typedef  int /*<<< orphan*/  PCHECK_DATA ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  pKeTryToAcquireSpinLockAtDpcLevel (int /*<<< orphan*/ ) ; 

BOOLEAN TryNoRaise(PKSPIN_LOCK SpinLock, PCHECK_DATA CheckData) {
    BOOLEAN Ret = pKeTryToAcquireSpinLockAtDpcLevel(SpinLock);
    return Ret;
}