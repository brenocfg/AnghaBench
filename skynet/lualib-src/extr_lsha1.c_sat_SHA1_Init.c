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

__attribute__((used)) static void sat_SHA1_Init(SHA1_CTX* context)
{
	/* SHA1	initialization constants */
	context->state[0] =	0x67452301;
	context->state[1] =	0xEFCDAB89;
	context->state[2] =	0x98BADCFE;
	context->state[3] =	0x10325476;
	context->state[4] =	0xC3D2E1F0;
	context->count[0] =	context->count[1] =	0;
}