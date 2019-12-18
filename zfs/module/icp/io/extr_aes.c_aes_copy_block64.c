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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  AES_COPY_BLOCK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IS_P2ALIGNED (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
aes_copy_block64(uint8_t *in, uint64_t *out)
{
	if (IS_P2ALIGNED(in, sizeof (uint64_t))) {
		/* LINTED: pointer alignment */
		out[0] = *(uint64_t *)&in[0];
		/* LINTED: pointer alignment */
		out[1] = *(uint64_t *)&in[8];
	} else {
		uint8_t *iv8 = (uint8_t *)&out[0];

		AES_COPY_BLOCK(in, iv8);
	}
}