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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  T ;

/* Variables and functions */
 int /*<<< orphan*/  R (int) ; 
 int /*<<< orphan*/ * SHA512_K ; 
 scalar_t__ a (int /*<<< orphan*/ ) ; 
 scalar_t__ b (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bswap64 (int /*<<< orphan*/ ) ; 
 scalar_t__ c (int /*<<< orphan*/ ) ; 
 scalar_t__ d (int /*<<< orphan*/ ) ; 
 scalar_t__ e (int /*<<< orphan*/ ) ; 
 scalar_t__ f (int /*<<< orphan*/ ) ; 
 scalar_t__ g (int /*<<< orphan*/ ) ; 
 scalar_t__ h (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isbigendian () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
transform512(uint64_t state[8], uint64_t data[16])
{
	const uint64_t *K = SHA512_K;
	uint64_t W[16];
	uint64_t T[8];
	unsigned int j;

	/* ensure big-endian integers */
	if (!isbigendian())
		for (j = 0; j < 16; j++)
			data[j] = bswap64(data[j]);

	/* Copy state[] to working vars. */
	memcpy(T, state, sizeof(T));

	/* 80 operations, partially loop unrolled */
	for (j = 0; j < 80; j+= 16) {
		R( 0); R( 1); R( 2); R( 3);
		R( 4); R( 5); R( 6); R( 7);
		R( 8); R( 9); R(10); R(11);
		R(12); R(13); R(14); R(15);
	}

	/* Add the working vars back into state[]. */
	state[0] += a(0);
	state[1] += b(0);
	state[2] += c(0);
	state[3] += d(0);
	state[4] += e(0);
	state[5] += f(0);
	state[6] += g(0);
	state[7] += h(0);
}