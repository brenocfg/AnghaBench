#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  u64; scalar_t__ u8; } ;
struct TYPE_5__ {int* count; TYPE_1__ buffer; int /*<<< orphan*/  state; } ;
typedef  TYPE_2__ fz_sha512 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  transform512 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fz_sha512_update(fz_sha512 *context, const unsigned char *input, size_t inlen)
{
	/* Copy the input data into a properly aligned temporary buffer.
	 * This way we can be called with arbitrarily sized buffers
	 * (no need to be multiple of 128 bytes), and the code works also
	 * on architectures that don't allow unaligned memory access. */
	while (inlen > 0)
	{
		const unsigned int copy_start = context->count[0] & 0x7F;
		unsigned int copy_size = 128 - copy_start;
		if (copy_size > inlen)
			copy_size = (unsigned int)inlen;

		memcpy(context->buffer.u8 + copy_start, input, copy_size);

		input += copy_size;
		inlen -= copy_size;
		context->count[0] += copy_size;
		/* carry overflow from low to high */
		if (context->count[0] < copy_size)
			context->count[1]++;

		if ((context->count[0] & 0x7F) == 0)
			transform512(context->state, context->buffer.u64);
	}
}