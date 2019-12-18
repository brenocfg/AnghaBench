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
typedef  int uint32_t ;

/* Variables and functions */
 int const* Td0 ; 
 int const* Td1 ; 
 int const* Td2 ; 
 int const* Td3 ; 
 int* Td4 ; 

__attribute__((used)) static void
aes_generic_decrypt(const uint32_t rk[], int Nr, const uint32_t ct[4],
    uint32_t pt[4])
{
	uint32_t s0, s1, s2, s3, t0, t1, t2, t3;
	int	 r;

	/*
	 * map byte array block to cipher state
	 * and add initial round key:
	 */
	s0 = ct[0] ^ rk[0];
	s1 = ct[1] ^ rk[1];
	s2 = ct[2] ^ rk[2];
	s3 = ct[3] ^ rk[3];

	/*
	 * Nr - 1 full rounds:
	 */

	r = Nr >> 1;

	for (;;) {
		t0 = Td0[s0 >> 24] ^
		    Td1[(s3 >> 16) & 0xff] ^
		    Td2[(s2 >> 8) & 0xff] ^
		    Td3[s1 & 0xff] ^
		    rk[4];

		t1 = Td0[s1 >> 24] ^
		    Td1[(s0 >> 16) & 0xff] ^
		    Td2[(s3 >>  8) & 0xff] ^
		    Td3[s2 & 0xff] ^
		    rk[5];

		t2 = Td0[s2 >> 24] ^
		    Td1[(s1 >> 16) & 0xff] ^
		    Td2[(s0 >>  8) & 0xff] ^
		    Td3[s3 & 0xff] ^
		    rk[6];

		t3 = Td0[s3 >> 24] ^
		    Td1[(s2 >> 16) & 0xff] ^
		    Td2[(s1 >> 8) & 0xff] ^
		    Td3[s0 & 0xff] ^
		    rk[7];

		rk += 8;

		if (--r == 0) {
			break;
		}

		s0 = Td0[t0 >> 24] ^
		    Td1[(t3 >> 16) & 0xff] ^
		    Td2[(t2 >> 8) & 0xff] ^
		    Td3[t1 & 0xff] ^
		    rk[0];

		s1 = Td0[t1 >> 24] ^
		    Td1[(t0 >> 16) & 0xff] ^
		    Td2[(t3 >> 8) & 0xff] ^
		    Td3[t2 & 0xff] ^
		    rk[1];

		s2 = Td0[t2 >> 24] ^
		    Td1[(t1 >> 16) & 0xff] ^
		    Td2[(t0 >> 8) & 0xff] ^
		    Td3[t3 & 0xff] ^
		    rk[2];

		s3 = Td0[t3 >> 24] ^
		    Td1[(t2 >> 16) & 0xff] ^
		    Td2[(t1 >> 8) & 0xff] ^
		    Td3[t0 & 0xff] ^
		    rk[3];
	}

	/*
	 * apply last round and
	 * map cipher state to byte array block:
	 */

	s0 = (Td4[t0 >> 24] & 0xff000000) ^
	    (Td4[(t3 >> 16) & 0xff] & 0x00ff0000) ^
	    (Td4[(t2 >> 8) & 0xff] & 0x0000ff00) ^
	    (Td4[t1 & 0xff] & 0x000000ff) ^
	    rk[0];
	pt[0] = s0;

	s1 = (Td4[t1 >> 24] & 0xff000000) ^
	    (Td4[(t0 >> 16) & 0xff] & 0x00ff0000) ^
	    (Td4[(t3 >>  8) & 0xff] & 0x0000ff00) ^
	    (Td4[t2 & 0xff] & 0x000000ff) ^
	    rk[1];
	pt[1] = s1;

	s2 = (Td4[t2 >> 24] & 0xff000000) ^
	    (Td4[(t1 >> 16) & 0xff] & 0x00ff0000) ^
	    (Td4[(t0 >> 8) & 0xff] & 0x0000ff00) ^
	    (Td4[t3 & 0xff] & 0x000000ff) ^
	    rk[2];
	pt[2] = s2;

	s3 = (Td4[t3 >> 24] & 0xff000000) ^
	    (Td4[(t2 >> 16) & 0xff] & 0x00ff0000) ^
	    (Td4[(t1 >>  8) & 0xff] & 0x0000ff00) ^
	    (Td4[t0 & 0xff] & 0x000000ff) ^
	    rk[3];
	pt[3] = s3;
}