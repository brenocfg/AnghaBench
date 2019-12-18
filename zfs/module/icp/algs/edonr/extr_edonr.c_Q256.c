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
 size_t EdonR256_BLOCK_BITSIZE ; 
 int /*<<< orphan*/  LS1_256 (int const,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  LS2_256 (int const,int,int,int,int,int,int,int,int) ; 
 int d (int) ; 
 int /*<<< orphan*/  quasi_exform256 (int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  s32 (int) ; 

__attribute__((used)) static size_t
Q256(size_t bitlen, const uint32_t *data, uint32_t *restrict p)
{
	size_t bl;

	for (bl = bitlen; bl >= EdonR256_BLOCK_BITSIZE;
	    bl -= EdonR256_BLOCK_BITSIZE, data += 16) {
		uint32_t s0, s1, s2, s3, s4, s5, s6, s7, t0, t1, t2, t3, t4,
		    t5, t6, t7;
		uint32_t p0, p1, p2, p3, p4, p5, p6, p7, q0, q1, q2, q3, q4,
		    q5, q6, q7;
		const uint32_t defix = 0xaaaaaaaa;
#if defined(MACHINE_IS_BIG_ENDIAN)
		uint32_t swp0, swp1, swp2, swp3, swp4, swp5, swp6, swp7, swp8,
		    swp9, swp10, swp11, swp12, swp13, swp14, swp15;
#define	d(j)	swp ## j
#define	s32(j)	ld_swap32((uint32_t *)data + j, swp ## j)
#else
#define	d(j)	data[j]
#endif

		/* First row of quasigroup e-transformations */
#if defined(MACHINE_IS_BIG_ENDIAN)
		s32(8);
		s32(9);
		s32(10);
		s32(11);
		s32(12);
		s32(13);
		s32(14);
		s32(15);
#endif
		LS1_256(defix, d(15), d(14), d(13), d(12), d(11), d(10), d(9),
		    d(8));
#if defined(MACHINE_IS_BIG_ENDIAN)
		s32(0);
		s32(1);
		s32(2);
		s32(3);
		s32(4);
		s32(5);
		s32(6);
		s32(7);
#undef s32
#endif
		LS2_256(defix, d(0), d(1), d(2), d(3), d(4), d(5), d(6), d(7));
		quasi_exform256(p0, p1, p2, p3, p4, p5, p6, p7);

		LS1_256(defix, p0, p1, p2, p3, p4, p5, p6, p7);
		LS2_256(defix, d(8), d(9), d(10), d(11), d(12), d(13), d(14),
		    d(15));
		quasi_exform256(q0, q1, q2, q3, q4, q5, q6, q7);

		/* Second row of quasigroup e-transformations */
		LS1_256(defix, p[8], p[9], p[10], p[11], p[12], p[13], p[14],
		    p[15]);
		LS2_256(defix, p0, p1, p2, p3, p4, p5, p6, p7);
		quasi_exform256(p0, p1, p2, p3, p4, p5, p6, p7);

		LS1_256(defix, p0, p1, p2, p3, p4, p5, p6, p7);
		LS2_256(defix, q0, q1, q2, q3, q4, q5, q6, q7);
		quasi_exform256(q0, q1, q2, q3, q4, q5, q6, q7);

		/* Third row of quasigroup e-transformations */
		LS1_256(defix, p0, p1, p2, p3, p4, p5, p6, p7);
		LS2_256(defix, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
		quasi_exform256(p0, p1, p2, p3, p4, p5, p6, p7);

		LS1_256(defix, q0, q1, q2, q3, q4, q5, q6, q7);
		LS2_256(defix, p0, p1, p2, p3, p4, p5, p6, p7);
		quasi_exform256(q0, q1, q2, q3, q4, q5, q6, q7);

		/* Fourth row of quasigroup e-transformations */
		LS1_256(defix, d(7), d(6), d(5), d(4), d(3), d(2), d(1), d(0));
		LS2_256(defix, p0, p1, p2, p3, p4, p5, p6, p7);
		quasi_exform256(p0, p1, p2, p3, p4, p5, p6, p7);

		LS1_256(defix, p0, p1, p2, p3, p4, p5, p6, p7);
		LS2_256(defix, q0, q1, q2, q3, q4, q5, q6, q7);
		quasi_exform256(q0, q1, q2, q3, q4, q5, q6, q7);

		/* Edon-R tweak on the original SHA-3 Edon-R submission. */
		p[0] ^= d(8) ^ p0;
		p[1] ^= d(9) ^ p1;
		p[2] ^= d(10) ^ p2;
		p[3] ^= d(11) ^ p3;
		p[4] ^= d(12) ^ p4;
		p[5] ^= d(13) ^ p5;
		p[6] ^= d(14) ^ p6;
		p[7] ^= d(15) ^ p7;
		p[8] ^= d(0) ^ q0;
		p[9] ^= d(1) ^ q1;
		p[10] ^= d(2) ^ q2;
		p[11] ^= d(3) ^ q3;
		p[12] ^= d(4) ^ q4;
		p[13] ^= d(5) ^ q5;
		p[14] ^= d(6) ^ q6;
		p[15] ^= d(7) ^ q7;
	}

#undef d
	return (bitlen - bl);
}