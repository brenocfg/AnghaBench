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
typedef  int /*<<< orphan*/  dst ;

/* Variables and functions */
 int /*<<< orphan*/  VDEV_RAIDZ_64MUL_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vdev_raidz_reconst_q_pre_func(void *dbuf, void *sbuf, size_t size,
    void *private)
{
	uint64_t *dst = dbuf;
	uint64_t *src = sbuf;
	uint64_t mask;
	int cnt = size / sizeof (dst[0]);

	for (int i = 0; i < cnt; i++, dst++, src++) {
		VDEV_RAIDZ_64MUL_2(*dst, mask);
		*dst ^= *src;
	}

	return (0);
}