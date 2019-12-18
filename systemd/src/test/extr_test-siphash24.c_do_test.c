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
typedef  int uint64_t ;
struct siphash {int v0; int v1; int v2; int v3; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int) ; 
 int siphash24 (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  siphash24_compress (int /*<<< orphan*/  const*,size_t,struct siphash*) ; 
 int siphash24_finalize (struct siphash*) ; 
 int /*<<< orphan*/  siphash24_init (struct siphash*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void do_test(const uint8_t *in, size_t len, const uint8_t *key) {
        struct siphash state = {};
        uint64_t out;
        unsigned i, j;

        out = siphash24(in, len, key);
        assert_se(out == 0xa129ca6149be45e5);

        /* verify the internal state as given in the above paper */
        siphash24_init(&state, key);
        assert_se(state.v0 == 0x7469686173716475);
        assert_se(state.v1 == 0x6b617f6d656e6665);
        assert_se(state.v2 == 0x6b7f62616d677361);
        assert_se(state.v3 == 0x7b6b696e727e6c7b);
        siphash24_compress(in, len, &state);
        assert_se(state.v0 == 0x4a017198de0a59e0);
        assert_se(state.v1 == 0x0d52f6f62a4f59a4);
        assert_se(state.v2 == 0x634cb3577b01fd3d);
        assert_se(state.v3 == 0xa5224d6f55c7d9c8);
        out = siphash24_finalize(&state);
        assert_se(out == 0xa129ca6149be45e5);
        assert_se(state.v0 == 0xf6bcd53893fecff1);
        assert_se(state.v1 == 0x54b9964c7ea0d937);
        assert_se(state.v2 == 0x1b38329c099bb55a);
        assert_se(state.v3 == 0x1814bb89ad7be679);

        /* verify that decomposing the input in three chunks gives the
           same result */
        for (i = 0; i < len; i++) {
                for (j = i; j < len; j++) {
                        siphash24_init(&state, key);
                        siphash24_compress(in, i, &state);
                        siphash24_compress(&in[i], j - i, &state);
                        siphash24_compress(&in[j], len - j, &state);
                        out = siphash24_finalize(&state);
                        assert_se(out == 0xa129ca6149be45e5);
                }
        }
}