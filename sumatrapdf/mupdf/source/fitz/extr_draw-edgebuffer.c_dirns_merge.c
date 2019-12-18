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

/* Variables and functions */
 int DIRN_UNSET ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dirns_match (int,int) ; 

__attribute__((used)) static inline int dirns_merge(int d0, int d1)
{
	if (d0 == DIRN_UNSET)
		return d1;
	assert(dirns_match(d0, d1));
	return d0;
}