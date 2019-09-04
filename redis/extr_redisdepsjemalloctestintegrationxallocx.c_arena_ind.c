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
typedef  int /*<<< orphan*/  ind ;

/* Variables and functions */
 int /*<<< orphan*/  assert_d_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mallctl (char*,void*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned
arena_ind(void) {
	static unsigned ind = 0;

	if (ind == 0) {
		size_t sz = sizeof(ind);
		assert_d_eq(mallctl("arenas.create", (void *)&ind, &sz, NULL,
		    0), 0, "Unexpected mallctl failure creating arena");
	}

	return ind;
}