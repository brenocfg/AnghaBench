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
typedef  int UINT8 ;
typedef  int UINT32 ;

/* Variables and functions */
 int galois_double_mask32 (int) ; 

void galois_double(UINT8* data, UINT32 len) {
    // FIXME - SIMD?

#ifdef _AMD64_
    while (len > sizeof(UINT64)) {
        UINT64 v = *((UINT64*)data), vv;

        vv = (v << 1) & 0xfefefefefefefefe;
        vv ^= galois_double_mask64(v) & 0x1d1d1d1d1d1d1d1d;
        *((UINT64*)data) = vv;

        data += sizeof(UINT64);
        len -= sizeof(UINT64);
    }
#else
    while (len > sizeof(UINT32)) {
        UINT32 v = *((UINT32*)data), vv;

        vv = (v << 1) & 0xfefefefe;
        vv ^= galois_double_mask32(v) & 0x1d1d1d1d;
        *((UINT32*)data) = vv;

        data += sizeof(UINT32);
        len -= sizeof(UINT32);
    }
#endif

    while (len > 0) {
        data[0] = (data[0] << 1) ^ ((data[0] & 0x80) ? 0x1d : 0);
        data++;
        len--;
    }
}