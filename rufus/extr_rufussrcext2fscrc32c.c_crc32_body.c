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
typedef  int uint32_t ;
typedef  size_t q ;

/* Variables and functions */
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline uint32_t
crc32_body(uint32_t crc, unsigned char const *buf, size_t len,
	   const uint32_t (*tab)[256])
{
# ifndef WORDS_BIGENDIAN
#  define DO_CRC(x) (crc = t0[(crc ^ (x)) & 255] ^ (crc >> 8))
#  define DO_CRC4 (t3[(q) & 255] ^ t2[(q >> 8) & 255] ^ \
		   t1[(q >> 16) & 255] ^ t0[(q >> 24) & 255])
#  define DO_CRC8 (t7[(q) & 255] ^ t6[(q >> 8) & 255] ^ \
		   t5[(q >> 16) & 255] ^ t4[(q >> 24) & 255])
# else
#  define DO_CRC(x) (crc = t0[((crc >> 24) ^ (x)) & 255] ^ (crc << 8))
#  define DO_CRC4 (t0[(q) & 255] ^ t1[(q >> 8) & 255] ^ \
		   t2[(q >> 16) & 255] ^ t3[(q >> 24) & 255])
#  define DO_CRC8 (t4[(q) & 255] ^ t5[(q >> 8) & 255] ^ \
		   t6[(q >> 16) & 255] ^ t7[(q >> 24) & 255])
# endif
	const uint32_t *b;
	size_t rem_len;
	const uint32_t *t0 = tab[0], *t1 = tab[1], *t2 = tab[2], *t3 = tab[3];
	const uint32_t *t4 = tab[4], *t5 = tab[5], *t6 = tab[6], *t7 = tab[7];
	uint32_t q;

	/* Align it */
	if (unlikely((uintptr_t)buf & 3 && len)) {
		do {
			DO_CRC(*buf++);
		} while ((--len) && ((uintptr_t)buf)&3);
	}

# if CRC_LE_BITS == 32
	rem_len = len & 3;
	len = len >> 2;
# else
	rem_len = len & 7;
	len = len >> 3;
# endif

	b = (const uint32_t *)buf;
	for (--b; len; --len) {
		q = crc ^ *++b; /* use pre increment for speed */
# if CRC_LE_BITS == 32
		crc = DO_CRC4;
# else
		crc = DO_CRC8;
		q = *++b;
		crc ^= DO_CRC4;
# endif
	}
	len = rem_len;
	/* And the last few bytes */
	if (len) {
		const uint8_t *p = (const uint8_t *)(b + 1) - 1;
		do {
			DO_CRC(*++p); /* use pre increment for speed */
		} while (--len);
	}
	return crc;
#undef DO_CRC
#undef DO_CRC4
#undef DO_CRC8
}