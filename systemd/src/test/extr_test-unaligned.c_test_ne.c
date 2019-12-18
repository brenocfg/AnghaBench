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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int) ; 
 int unaligned_read_ne16 (int*) ; 
 int unaligned_read_ne32 (int*) ; 
 int unaligned_read_ne64 (int*) ; 
 int /*<<< orphan*/  unaligned_write_ne16 (int*,int) ; 
 int /*<<< orphan*/  unaligned_write_ne32 (int*,int) ; 
 int /*<<< orphan*/  unaligned_write_ne64 (int*,int) ; 

__attribute__((used)) static void test_ne(void) {
        uint16_t x = 4711;
        uint32_t y = 123456;
        uint64_t z = 9876543210;

        /* Note that we don't bother actually testing alignment issues in this function, after all the _ne() functions
         * are just aliases for the _le() or _be() implementations, which we test extensively above. Hence, in this
         * function, just ensure that they map to the right version on the local architecture. */

        assert_se(unaligned_read_ne16(&x) == 4711);
        assert_se(unaligned_read_ne32(&y) == 123456);
        assert_se(unaligned_read_ne64(&z) == 9876543210);

        unaligned_write_ne16(&x, 1);
        unaligned_write_ne32(&y, 2);
        unaligned_write_ne64(&z, 3);

        assert_se(x == 1);
        assert_se(y == 2);
        assert_se(z == 3);
}