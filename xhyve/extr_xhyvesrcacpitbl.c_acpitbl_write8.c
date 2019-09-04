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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
acpitbl_write8(void *base, uint64_t offset, uint8_t val) {
	memcpy(((void *) (((uintptr_t) base) + offset)), &val, 1);
}