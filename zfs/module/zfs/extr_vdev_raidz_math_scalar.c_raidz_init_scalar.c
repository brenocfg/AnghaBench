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

/* Variables and functions */
 int /*<<< orphan*/  gf_mul (int,int) ; 
 int /*<<< orphan*/ ** vdev_raidz_mul_lt ; 

__attribute__((used)) static void
raidz_init_scalar(void)
{
	int c, i;
	for (c = 0; c < 256; c++)
		for (i = 0; i < 256; i++)
			vdev_raidz_mul_lt[c][i] = gf_mul(c, i);

}