#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int inbufBitCount; scalar_t__ inbufPos; scalar_t__ inbufCount; int* inbuf; int inbufBits; int /*<<< orphan*/  jmpbuf; int /*<<< orphan*/  in_fd; } ;
typedef  TYPE_1__ bunzip_data ;

/* Variables and functions */
 int /*<<< orphan*/  IOBUF_SIZE ; 
 int /*<<< orphan*/  RETVAL_UNEXPECTED_INPUT_EOF ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ safe_read (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned get_bits(bunzip_data *bd, int bits_wanted)
{
	unsigned bits = 0;
	/* Cache bd->inbufBitCount in a CPU register (hopefully): */
	int bit_count = bd->inbufBitCount;

	/* If we need to get more data from the byte buffer, do so.  (Loop getting
	   one byte at a time to enforce endianness and avoid unaligned access.) */
	while (bit_count < bits_wanted) {

		/* If we need to read more data from file into byte buffer, do so */
		if (bd->inbufPos == bd->inbufCount) {
			/* if "no input fd" case: in_fd == -1, read fails, we jump */
			bd->inbufCount = safe_read(bd->in_fd, bd->inbuf, IOBUF_SIZE);
			if (bd->inbufCount <= 0)
				longjmp(bd->jmpbuf, RETVAL_UNEXPECTED_INPUT_EOF);
			bd->inbufPos = 0;
		}

		/* Avoid 32-bit overflow (dump bit buffer to top of output) */
		if (bit_count >= 24) {
			bits = bd->inbufBits & ((1 << bit_count) - 1);
			bits_wanted -= bit_count;
			bits <<= bits_wanted;
			bit_count = 0;
		}

		/* Grab next 8 bits of input from buffer. */
		bd->inbufBits = (bd->inbufBits << 8) | bd->inbuf[bd->inbufPos++];
		bit_count += 8;
	}

	/* Calculate result */
	bit_count -= bits_wanted;
	bd->inbufBitCount = bit_count;
	bits |= (bd->inbufBits >> bit_count) & ((1 << bits_wanted) - 1);

	return bits;
}