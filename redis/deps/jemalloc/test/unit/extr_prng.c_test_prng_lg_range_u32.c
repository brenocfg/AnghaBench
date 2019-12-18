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
typedef  unsigned int uint32_t ;
typedef  int /*<<< orphan*/  atomic_u32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 unsigned int UINT32_C (int) ; 
 int /*<<< orphan*/  assert_u32_eq (unsigned int,unsigned int,char*,...) ; 
 int /*<<< orphan*/  assert_u32_ne (unsigned int,unsigned int,char*) ; 
 int /*<<< orphan*/  atomic_store_u32 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 unsigned int prng_lg_range_u32 (int /*<<< orphan*/ *,unsigned int,int) ; 

__attribute__((used)) static void
test_prng_lg_range_u32(bool atomic) {
	atomic_u32_t sa, sb;
	uint32_t ra, rb;
	unsigned lg_range;

	atomic_store_u32(&sa, 42, ATOMIC_RELAXED);
	ra = prng_lg_range_u32(&sa, 32, atomic);
	atomic_store_u32(&sa, 42, ATOMIC_RELAXED);
	rb = prng_lg_range_u32(&sa, 32, atomic);
	assert_u32_eq(ra, rb,
	    "Repeated generation should produce repeated results");

	atomic_store_u32(&sb, 42, ATOMIC_RELAXED);
	rb = prng_lg_range_u32(&sb, 32, atomic);
	assert_u32_eq(ra, rb,
	    "Equivalent generation should produce equivalent results");

	atomic_store_u32(&sa, 42, ATOMIC_RELAXED);
	ra = prng_lg_range_u32(&sa, 32, atomic);
	rb = prng_lg_range_u32(&sa, 32, atomic);
	assert_u32_ne(ra, rb,
	    "Full-width results must not immediately repeat");

	atomic_store_u32(&sa, 42, ATOMIC_RELAXED);
	ra = prng_lg_range_u32(&sa, 32, atomic);
	for (lg_range = 31; lg_range > 0; lg_range--) {
		atomic_store_u32(&sb, 42, ATOMIC_RELAXED);
		rb = prng_lg_range_u32(&sb, lg_range, atomic);
		assert_u32_eq((rb & (UINT32_C(0xffffffff) << lg_range)),
		    0, "High order bits should be 0, lg_range=%u", lg_range);
		assert_u32_eq(rb, (ra >> (32 - lg_range)),
		    "Expected high order bits of full-width result, "
		    "lg_range=%u", lg_range);
	}
}