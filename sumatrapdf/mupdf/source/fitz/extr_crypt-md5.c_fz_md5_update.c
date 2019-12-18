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
struct TYPE_3__ {int* count; unsigned char const* buffer; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ fz_md5 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char const*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  transform (int /*<<< orphan*/ ,unsigned char const*) ; 

void fz_md5_update(fz_md5 *context, const unsigned char *input, size_t inlen)
{
	size_t i, index, partlen;

	/* Compute number of bytes mod 64 */
	index = (size_t)((context->count[0] >> 3) & 0x3F);

	/* Update number of bits */
	context->count[0] += (unsigned int) inlen << 3;
	if (context->count[0] < (unsigned int) inlen << 3)
		context->count[1] ++;
	context->count[1] += (unsigned int) inlen >> 29;

	partlen = 64 - index;

	/* Transform as many times as possible. */
	if (inlen >= partlen)
	{
		memcpy(context->buffer + index, input, partlen);
		transform(context->state, context->buffer);

		for (i = partlen; i + 63 < inlen; i += 64)
			transform(context->state, input + i);

		index = 0;
	}
	else
	{
		i = 0;
	}

	/* Buffer remaining input */
	memcpy(context->buffer + index, input + i, inlen - i);
}