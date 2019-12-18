#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* u8; int* u64; } ;
struct TYPE_6__ {int* count; int* state; TYPE_1__ buffer; } ;
typedef  TYPE_2__ fz_sha512 ;

/* Variables and functions */
 void* bswap64 (int) ; 
 int /*<<< orphan*/  isbigendian () ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  transform512 (int*,int*) ; 

void fz_sha512_final(fz_sha512 *context, unsigned char digest[64])
{
	/* Add padding as described in RFC 3174 (it describes SHA-1 but
	 * the same padding style is used for SHA-512 too). */
	unsigned int j = context->count[0] & 0x7F;
	context->buffer.u8[j++] = 0x80;

	while (j != 112)
	{
		if (j == 128)
		{
			transform512(context->state, context->buffer.u64);
			j = 0;
		}
		context->buffer.u8[j++] = 0x00;
	}

	/* Convert the message size from bytes to bits. */
	context->count[1] = (context->count[1] << 3) + (context->count[0] >> 29);
	context->count[0] = context->count[0] << 3;

	if (!isbigendian())
	{
		context->buffer.u64[14] = bswap64(context->count[1]);
		context->buffer.u64[15] = bswap64(context->count[0]);
	}
	else
	{
		context->buffer.u64[14] = context->count[1];
		context->buffer.u64[15] = context->count[0];
	}
	transform512(context->state, context->buffer.u64);

	if (!isbigendian())
		for (j = 0; j < 8; j++)
			context->state[j] = bswap64(context->state[j]);

	memcpy(digest, &context->state[0], 64);
	memset(context, 0, sizeof(fz_sha512));
}