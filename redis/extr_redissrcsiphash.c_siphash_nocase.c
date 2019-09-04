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

/* Variables and functions */
 int /*<<< orphan*/  SIPROUND ; 
 int /*<<< orphan*/  U64TO8_LE (int /*<<< orphan*/ *,int) ; 
 int U8TO64_LE (int /*<<< orphan*/  const*) ; 
 int U8TO64_LE_NOCASE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  siptlw (int /*<<< orphan*/  const) ; 

uint64_t siphash_nocase(const uint8_t *in, const size_t inlen, const uint8_t *k)
{
#ifndef UNALIGNED_LE_CPU
    uint64_t hash;
    uint8_t *out = (uint8_t*) &hash;
#endif
    uint64_t v0 = 0x736f6d6570736575ULL;
    uint64_t v1 = 0x646f72616e646f6dULL;
    uint64_t v2 = 0x6c7967656e657261ULL;
    uint64_t v3 = 0x7465646279746573ULL;
    uint64_t k0 = U8TO64_LE(k);
    uint64_t k1 = U8TO64_LE(k + 8);
    uint64_t m;
    const uint8_t *end = in + inlen - (inlen % sizeof(uint64_t));
    const int left = inlen & 7;
    uint64_t b = ((uint64_t)inlen) << 56;
    v3 ^= k1;
    v2 ^= k0;
    v1 ^= k1;
    v0 ^= k0;

    for (; in != end; in += 8) {
        m = U8TO64_LE_NOCASE(in);
        v3 ^= m;

        SIPROUND;

        v0 ^= m;
    }

    switch (left) {
    case 7: b |= ((uint64_t)siptlw(in[6])) << 48; /* fall-thru */
    case 6: b |= ((uint64_t)siptlw(in[5])) << 40; /* fall-thru */
    case 5: b |= ((uint64_t)siptlw(in[4])) << 32; /* fall-thru */
    case 4: b |= ((uint64_t)siptlw(in[3])) << 24; /* fall-thru */
    case 3: b |= ((uint64_t)siptlw(in[2])) << 16; /* fall-thru */
    case 2: b |= ((uint64_t)siptlw(in[1])) << 8; /* fall-thru */
    case 1: b |= ((uint64_t)siptlw(in[0])); break;
    case 0: break;
    }

    v3 ^= b;

    SIPROUND;

    v0 ^= b;
    v2 ^= 0xff;

    SIPROUND;
    SIPROUND;

    b = v0 ^ v1 ^ v2 ^ v3;
#ifndef UNALIGNED_LE_CPU
    U64TO8_LE(out, b);
    return hash;
#else
    return b;
#endif
}