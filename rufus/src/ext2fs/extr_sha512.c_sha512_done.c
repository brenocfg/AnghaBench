#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int length; int curlen; unsigned char* buf; int* state; } ;
struct hash_state {TYPE_1__ sha512; } ;

/* Variables and functions */
 int CONST64 (int) ; 
 int /*<<< orphan*/  STORE64H (int,unsigned char*) ; 
 int /*<<< orphan*/  sha512_compress (struct hash_state*,unsigned char*) ; 

__attribute__((used)) static void sha512_done(struct hash_state * md, unsigned char *out)
{
	int i;

	/* increase the length of the message */
	md->sha512.length += md->sha512.curlen * CONST64(8);

	/* append the '1' bit */
	md->sha512.buf[md->sha512.curlen++] = (unsigned char)0x80;

	/* if the length is currently above 112 bytes we append zeros then
	 * compress. Then we can fall back to padding zeros and length encoding
	 * like normal. */
	if (md->sha512.curlen > 112) {
		while (md->sha512.curlen < 128) {
			md->sha512.buf[md->sha512.curlen++] = (unsigned char)0;
		}
		sha512_compress(md, md->sha512.buf);
		md->sha512.curlen = 0;
	}

	/* pad upto 120 bytes of zeroes note: that from 112 to 120 is the 64 MSB
	 * of the length. We assume that you won't hash > 2^64 bits of data. */
	while (md->sha512.curlen < 120) {
		md->sha512.buf[md->sha512.curlen++] = (unsigned char)0;
	}

	/* store length */
	STORE64H(md->sha512.length, md->sha512.buf + 120);
	sha512_compress(md, md->sha512.buf);

	/* copy output */
	for (i = 0; i < 8; i++) {
		STORE64H(md->sha512.state[i], out+(8 * i));
	}
}