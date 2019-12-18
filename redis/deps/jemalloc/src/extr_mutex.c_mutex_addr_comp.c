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
typedef  int /*<<< orphan*/  witness_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mutex_addr_comp(const witness_t *witness1, void *mutex1,
    const witness_t *witness2, void *mutex2) {
	assert(mutex1 != NULL);
	assert(mutex2 != NULL);
	uintptr_t mu1int = (uintptr_t)mutex1;
	uintptr_t mu2int = (uintptr_t)mutex2;
	if (mu1int < mu2int) {
		return -1;
	} else if (mu1int == mu2int) {
		return 0;
	} else {
		return 1;
	}
}