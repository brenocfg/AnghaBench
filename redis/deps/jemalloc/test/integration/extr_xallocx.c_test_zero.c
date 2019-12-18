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
 int FILL_BYTE ; 
 int MALLOCX_ARENA (int /*<<< orphan*/ ) ; 
 int MALLOCX_ZERO ; 
 int /*<<< orphan*/  arena_ind () ; 
 int /*<<< orphan*/  assert_false (int /*<<< orphan*/ ,char*,size_t,...) ; 
 int /*<<< orphan*/  assert_ptr_not_null (void*,char*) ; 
 int /*<<< orphan*/  dallocx (void*,int) ; 
 void* mallocx (size_t,int) ; 
 int /*<<< orphan*/  memset (void*,int,size_t) ; 
 size_t nallocx (size_t,int) ; 
 void* rallocx (void*,size_t,int) ; 
 int /*<<< orphan*/  validate_fill (void*,int,size_t,size_t) ; 
 size_t xallocx (void*,size_t,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
test_zero(size_t szmin, size_t szmax) {
	int flags = MALLOCX_ARENA(arena_ind()) | MALLOCX_ZERO;
	size_t sz, nsz;
	void *p;
#define FILL_BYTE 0x7aU

	sz = szmax;
	p = mallocx(sz, flags);
	assert_ptr_not_null(p, "Unexpected mallocx() error");
	assert_false(validate_fill(p, 0x00, 0, sz), "Memory not filled: sz=%zu",
	    sz);

	/*
	 * Fill with non-zero so that non-debug builds are more likely to detect
	 * errors.
	 */
	memset(p, FILL_BYTE, sz);
	assert_false(validate_fill(p, FILL_BYTE, 0, sz),
	    "Memory not filled: sz=%zu", sz);

	/* Shrink in place so that we can expect growing in place to succeed. */
	sz = szmin;
	if (xallocx(p, sz, 0, flags) != sz) {
		p = rallocx(p, sz, flags);
		assert_ptr_not_null(p, "Unexpected rallocx() failure");
	}
	assert_false(validate_fill(p, FILL_BYTE, 0, sz),
	    "Memory not filled: sz=%zu", sz);

	for (sz = szmin; sz < szmax; sz = nsz) {
		nsz = nallocx(sz+1, flags);
		if (xallocx(p, sz+1, 0, flags) != nsz) {
			p = rallocx(p, sz+1, flags);
			assert_ptr_not_null(p, "Unexpected rallocx() failure");
		}
		assert_false(validate_fill(p, FILL_BYTE, 0, sz),
		    "Memory not filled: sz=%zu", sz);
		assert_false(validate_fill(p, 0x00, sz, nsz-sz),
		    "Memory not filled: sz=%zu, nsz-sz=%zu", sz, nsz-sz);
		memset((void *)((uintptr_t)p + sz), FILL_BYTE, nsz-sz);
		assert_false(validate_fill(p, FILL_BYTE, 0, nsz),
		    "Memory not filled: nsz=%zu", nsz);
	}

	dallocx(p, flags);
}