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
 int const* Te0 ; 
 int const* Te1 ; 
 int const* Te2 ; 
 int const* Te3 ; 
 int* Te4 ; 

__attribute__((used)) static void
aes_generic_encrypt(const uint32_t rk[], int Nr, const uint32_t pt[4],
    uint32_t ct[4])
{
	uint32_t	s0, s1, s2, s3, t0, t1, t2, t3;
	int		r;

	/*
	 * map byte array block to cipher state
	 * and add initial round key:
	 */

	s0 = pt[0] ^ rk[0];
	s1 = pt[1] ^ rk[1];
	s2 = pt[2] ^ rk[2];
	s3 = pt[3] ^ rk[3];

	/*
	 * Nr - 1 full rounds:
	 */

	r = Nr >> 1;

	for (;;) {
		t0 = Te0[s0 >> 24] ^
		    Te1[(s1 >> 16) & 0xff] ^
		    Te2[(s2 >>  8) & 0xff] ^
		    Te3[s3 & 0xff] ^
		    rk[4];

		t1 = Te0[s1 >> 24] ^
		    Te1[(s2 >> 16) & 0xff] ^
		    Te2[(s3 >>  8) & 0xff] ^
		    Te3[s0 & 0xff] ^
		    rk[5];

		t2 = Te0[s2 >> 24] ^
		    Te1[(s3 >> 16) & 0xff] ^
		    Te2[(s0 >>  8) & 0xff] ^
		    Te3[s1 & 0xff] ^
		    rk[6];

		t3 = Te0[s3 >> 24] ^
		    Te1[(s0 >> 16) & 0xff] ^
		    Te2[(s1 >>  8) & 0xff] ^
		    Te3[s2 & 0xff] ^
		    rk[7];

		rk += 8;

		if (--r == 0) {
			break;
		}

		s0 = Te0[t0 >> 24] ^
		    Te1[(t1 >> 16) & 0xff] ^
		    Te2[(t2 >>  8) & 0xff] ^
		    Te3[t3 & 0xff] ^
		    rk[0];

		s1 = Te0[t1 >> 24] ^
		    Te1[(t2 >> 16) & 0xff] ^
		    Te2[(t3 >>  8) & 0xff] ^
		    Te3[t0 & 0xff] ^
		    rk[1];

		s2 = Te0[t2 >> 24] ^
		    Te1[(t3 >> 16) & 0xff] ^
		    Te2[(t0 >>  8) & 0xff] ^
		    Te3[t1 & 0xff] ^
		    rk[2];

		s3 = Te0[t3 >> 24] ^
		    Te1[(t0 >> 16) & 0xff] ^
		    Te2[(t1 >>  8) & 0xff] ^
		    Te3[t2 & 0xff] ^
		    rk[3];
	}

	/*
	 * apply last round and
	 * map cipher state to byte array block:
	 */

	s0 = (Te4[(t0 >> 24)] & 0xff000000) ^
	    (Te4[(t1 >> 16) & 0xff] & 0x00ff0000) ^
	    (Te4[(t2 >>  8) & 0xff] & 0x0000ff00) ^
	    (Te4[t3 & 0xff] & 0x000000ff) ^
	    rk[0];
	ct[0] = s0;

	s1 = (Te4[(t1 >> 24)] & 0xff000000) ^
	    (Te4[(t2 >> 16) & 0xff] & 0x00ff0000) ^
	    (Te4[(t3 >>  8) & 0xff] & 0x0000ff00) ^
	    (Te4[t0 & 0xff] & 0x000000ff) ^
	    rk[1];
	ct[1] = s1;

	s2 = (Te4[(t2 >> 24)] & 0xff000000) ^
	    (Te4[(t3 >> 16) & 0xff] & 0x00ff0000) ^
	    (Te4[(t0 >>  8) & 0xff] & 0x0000ff00) ^
	    (Te4[t1 & 0xff] & 0x000000ff) ^
	    rk[2];
	ct[2] = s2;

	s3 = (Te4[(t3 >> 24)] & 0xff000000) ^
	    (Te4[(t0 >> 16) & 0xff] & 0x00ff0000) ^
	    (Te4[(t1 >>  8) & 0xff] & 0x0000ff00) ^
	    (Te4[t2 & 0xff] & 0x000000ff) ^
	    rk[3];
	ct[3] = s3;
}