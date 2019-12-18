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
typedef  int uint8_t ;
struct siphash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ memcmp (struct siphash*,struct siphash*,int) ; 
 int /*<<< orphan*/  siphash24_compress (int const*,unsigned int,struct siphash*) ; 
 int /*<<< orphan*/  siphash24_init (struct siphash*,int const*) ; 
 int /*<<< orphan*/  zero (int*) ; 

__attribute__((used)) static void test_short_hashes(void) {
        const uint8_t one[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                                0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16 };
        const uint8_t  key[16] = { 0x22, 0x24, 0x41, 0x22, 0x55, 0x77, 0x88, 0x07,
                                   0x23, 0x09, 0x23, 0x14, 0x0c, 0x33, 0x0e, 0x0f};
        uint8_t two[sizeof one] = {};

        struct siphash state1 = {}, state2 = {};
        unsigned i, j;

        siphash24_init(&state1, key);
        siphash24_init(&state2, key);

        /* hashing 1, 2, 3, 4, 5, ..., 16 bytes, with the byte after the buffer different */
        for (i = 1; i <= sizeof one; i++) {
                siphash24_compress(one, i, &state1);

                two[i-1] = one[i-1];
                siphash24_compress(two, i, &state2);

                assert_se(memcmp(&state1, &state2, sizeof state1) == 0);
        }

        /* hashing n and 1, n and 2, n and 3, ..., n-1 and 1, n-2 and 2, ... */
        for (i = sizeof one; i > 0; i--) {
                zero(two);

                for (j = 1; j <= sizeof one; j++) {
                        siphash24_compress(one, i, &state1);
                        siphash24_compress(one, j, &state1);

                        siphash24_compress(one, i, &state2);
                        two[j-1] = one[j-1];
                        siphash24_compress(two, j, &state2);

                        assert_se(memcmp(&state1, &state2, sizeof state1) == 0);
                }
        }
}