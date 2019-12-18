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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/ * data ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int unaligned_read_be16 (int /*<<< orphan*/ *) ; 
 int unaligned_read_be32 (int /*<<< orphan*/ *) ; 
 int unaligned_read_be64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unaligned_write_be16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  unaligned_write_be32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  unaligned_write_be64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_be(void) {
        uint8_t scratch[16];

        assert_se(unaligned_read_be16(&data[0]) == 0x0001);
        assert_se(unaligned_read_be16(&data[1]) == 0x0102);

        assert_se(unaligned_read_be32(&data[0]) == 0x00010203);
        assert_se(unaligned_read_be32(&data[1]) == 0x01020304);
        assert_se(unaligned_read_be32(&data[2]) == 0x02030405);
        assert_se(unaligned_read_be32(&data[3]) == 0x03040506);

        assert_se(unaligned_read_be64(&data[0]) == 0x0001020304050607);
        assert_se(unaligned_read_be64(&data[1]) == 0x0102030405060708);
        assert_se(unaligned_read_be64(&data[2]) == 0x0203040506070809);
        assert_se(unaligned_read_be64(&data[3]) == 0x030405060708090a);
        assert_se(unaligned_read_be64(&data[4]) == 0x0405060708090a0b);
        assert_se(unaligned_read_be64(&data[5]) == 0x05060708090a0b0c);
        assert_se(unaligned_read_be64(&data[6]) == 0x060708090a0b0c0d);
        assert_se(unaligned_read_be64(&data[7]) == 0x0708090a0b0c0d0e);

        zero(scratch);
        unaligned_write_be16(&scratch[0], 0x0001);
        assert_se(memcmp(&scratch[0], &data[0], sizeof(uint16_t)) == 0);
        zero(scratch);
        unaligned_write_be16(&scratch[1], 0x0102);
        assert_se(memcmp(&scratch[1], &data[1], sizeof(uint16_t)) == 0);

        zero(scratch);
        unaligned_write_be32(&scratch[0], 0x00010203);
        assert_se(memcmp(&scratch[0], &data[0], sizeof(uint32_t)) == 0);
        zero(scratch);
        unaligned_write_be32(&scratch[1], 0x01020304);
        assert_se(memcmp(&scratch[1], &data[1], sizeof(uint32_t)) == 0);
        zero(scratch);
        unaligned_write_be32(&scratch[2], 0x02030405);
        assert_se(memcmp(&scratch[2], &data[2], sizeof(uint32_t)) == 0);
        zero(scratch);
        unaligned_write_be32(&scratch[3], 0x03040506);
        assert_se(memcmp(&scratch[3], &data[3], sizeof(uint32_t)) == 0);

        zero(scratch);
        unaligned_write_be64(&scratch[0], 0x0001020304050607);
        assert_se(memcmp(&scratch[0], &data[0], sizeof(uint64_t)) == 0);
        zero(scratch);
        unaligned_write_be64(&scratch[1], 0x0102030405060708);
        assert_se(memcmp(&scratch[1], &data[1], sizeof(uint64_t)) == 0);
        zero(scratch);
        unaligned_write_be64(&scratch[2], 0x0203040506070809);
        assert_se(memcmp(&scratch[2], &data[2], sizeof(uint64_t)) == 0);
        zero(scratch);
        unaligned_write_be64(&scratch[3], 0x030405060708090a);
        assert_se(memcmp(&scratch[3], &data[3], sizeof(uint64_t)) == 0);
        zero(scratch);
        unaligned_write_be64(&scratch[4], 0x0405060708090a0b);
        assert_se(memcmp(&scratch[4], &data[4], sizeof(uint64_t)) == 0);
        zero(scratch);
        unaligned_write_be64(&scratch[5], 0x05060708090a0b0c);
        assert_se(memcmp(&scratch[5], &data[5], sizeof(uint64_t)) == 0);
        zero(scratch);
        unaligned_write_be64(&scratch[6], 0x060708090a0b0c0d);
        assert_se(memcmp(&scratch[6], &data[6], sizeof(uint64_t)) == 0);
        zero(scratch);
        unaligned_write_be64(&scratch[7], 0x0708090a0b0c0d0e);
        assert_se(memcmp(&scratch[7], &data[7], sizeof(uint64_t)) == 0);
}