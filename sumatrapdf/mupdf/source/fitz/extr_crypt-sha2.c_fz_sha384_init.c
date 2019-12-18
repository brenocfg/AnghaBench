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
struct TYPE_3__ {int* state; scalar_t__* count; } ;
typedef  TYPE_1__ fz_sha384 ;

/* Variables and functions */

void fz_sha384_init(fz_sha384 *context)
{
	context->count[0] = context->count[1] = 0;

	context->state[0] = 0xCBBB9D5DC1059ED8ull;
	context->state[1] = 0x629A292A367CD507ull;
	context->state[2] = 0x9159015A3070DD17ull;
	context->state[3] = 0x152FECD8F70E5939ull;
	context->state[4] = 0x67332667FFC00B31ull;
	context->state[5] = 0x8EB44A8768581511ull;
	context->state[6] = 0xDB0C2E0D64F98FA7ull;
	context->state[7] = 0x47B5481DBEFA4FA4ull;
}