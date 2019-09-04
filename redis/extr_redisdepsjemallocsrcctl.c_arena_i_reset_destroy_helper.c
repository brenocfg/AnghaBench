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
typedef  int /*<<< orphan*/  tsd_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  MIB_UNSIGNED (unsigned int,int) ; 
 int /*<<< orphan*/  READONLY () ; 
 int /*<<< orphan*/  WRITEONLY () ; 
 int /*<<< orphan*/ * arena_get (int /*<<< orphan*/ ,unsigned int,int) ; 
 scalar_t__ arena_is_auto (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
arena_i_reset_destroy_helper(tsd_t *tsd, const size_t *mib, size_t miblen,
    void *oldp, size_t *oldlenp, void *newp, size_t newlen, unsigned *arena_ind,
    arena_t **arena) {
	int ret;

	READONLY();
	WRITEONLY();
	MIB_UNSIGNED(*arena_ind, 1);

	*arena = arena_get(tsd_tsdn(tsd), *arena_ind, false);
	if (*arena == NULL || arena_is_auto(*arena)) {
		ret = EFAULT;
		goto label_return;
	}

	ret = 0;
label_return:
	return ret;
}