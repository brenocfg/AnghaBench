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
typedef  TYPE_1__ SHA1_CTX ;

/* Variables and functions */

void
SHA1Init(SHA1_CTX *ctx)
{
	ctx->count[0] = ctx->count[1] = 0;

	/*
	 * load magic initialization constants. Tell lint
	 * that these constants are unsigned by using U.
	 */

	ctx->state[0] = 0x67452301U;
	ctx->state[1] = 0xefcdab89U;
	ctx->state[2] = 0x98badcfeU;
	ctx->state[3] = 0x10325476U;
	ctx->state[4] = 0xc3d2e1f0U;
}