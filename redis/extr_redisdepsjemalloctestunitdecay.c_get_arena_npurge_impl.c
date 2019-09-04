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
typedef  int /*<<< orphan*/  npurge ;
typedef  int /*<<< orphan*/  mib ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  assert_d_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ config_stats ; 
 int /*<<< orphan*/  mallctlbymib (size_t*,size_t,void*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mallctlnametomib (char const*,size_t*,size_t*) ; 

__attribute__((used)) static uint64_t
get_arena_npurge_impl(const char *mibname, unsigned arena_ind) {
	size_t mib[4];
	size_t miblen = sizeof(mib)/sizeof(size_t);
	assert_d_eq(mallctlnametomib(mibname, mib, &miblen), 0,
	    "Unexpected mallctlnametomib() failure");
	mib[2] = (size_t)arena_ind;
	uint64_t npurge = 0;
	size_t sz = sizeof(npurge);
	assert_d_eq(mallctlbymib(mib, miblen, (void *)&npurge, &sz, NULL, 0),
	    config_stats ? 0 : ENOENT, "Unexpected mallctlbymib() failure");
	return npurge;
}