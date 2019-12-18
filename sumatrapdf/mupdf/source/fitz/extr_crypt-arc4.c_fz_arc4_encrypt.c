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
typedef  int /*<<< orphan*/  fz_arc4 ;

/* Variables and functions */
 unsigned char fz_arc4_next (int /*<<< orphan*/ *) ; 

void
fz_arc4_encrypt(fz_arc4 *arc4, unsigned char *dest, const unsigned char *src, size_t len)
{
	size_t i;
	for (i = 0; i < len; i++)
	{
		unsigned char x;
		x = fz_arc4_next(arc4);
		dest[i] = src[i] ^ x;
	}
}