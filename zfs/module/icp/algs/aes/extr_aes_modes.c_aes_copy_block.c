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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AES_COPY_BLOCK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IS_P2ALIGNED2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void
aes_copy_block(uint8_t *in, uint8_t *out)
{
	if (IS_P2ALIGNED2(in, out, sizeof (uint32_t))) {
		/* LINTED: pointer alignment */
		*(uint32_t *)&out[0] = *(uint32_t *)&in[0];
		/* LINTED: pointer alignment */
		*(uint32_t *)&out[4] = *(uint32_t *)&in[4];
		/* LINTED: pointer alignment */
		*(uint32_t *)&out[8] = *(uint32_t *)&in[8];
		/* LINTED: pointer alignment */
		*(uint32_t *)&out[12] = *(uint32_t *)&in[12];
	} else {
		AES_COPY_BLOCK(in, out);
	}
}