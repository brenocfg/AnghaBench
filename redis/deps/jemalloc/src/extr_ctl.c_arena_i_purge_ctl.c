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

/* Variables and functions */
 int /*<<< orphan*/  MIB_UNSIGNED (unsigned int,int) ; 
 int /*<<< orphan*/  READONLY () ; 
 int /*<<< orphan*/  WRITEONLY () ; 
 int /*<<< orphan*/  arena_i_decay (int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
arena_i_purge_ctl(tsd_t *tsd, const size_t *mib, size_t miblen, void *oldp,
    size_t *oldlenp, void *newp, size_t newlen) {
	int ret;
	unsigned arena_ind;

	READONLY();
	WRITEONLY();
	MIB_UNSIGNED(arena_ind, 1);
	arena_i_decay(tsd_tsdn(tsd), arena_ind, true);

	ret = 0;
label_return:
	return ret;
}