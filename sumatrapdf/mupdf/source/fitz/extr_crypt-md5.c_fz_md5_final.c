#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* count; int* state; } ;
typedef  TYPE_1__ fz_md5 ;

/* Variables and functions */
 int /*<<< orphan*/  encode (unsigned char*,int*,int) ; 
 int /*<<< orphan*/  fz_md5_update (TYPE_1__*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 unsigned char* padding ; 

void fz_md5_final(fz_md5 *context, unsigned char digest[16])
{
	unsigned char bits[8];
	unsigned index, padlen;

	/* Save number of bits */
	encode(bits, context->count, 8);

	/* Pad out to 56 mod 64 */
	index = (unsigned)((context->count[0] >> 3) & 0x3f);
	padlen = index < 56 ? 56 - index : 120 - index;
	fz_md5_update(context, padding, padlen);

	/* Append length (before padding) */
	fz_md5_update(context, bits, 8);

	/* Store state in digest */
	encode(digest, context->state, 16);

	/* Zeroize sensitive information */
	memset(context, 0, sizeof(fz_md5));
}