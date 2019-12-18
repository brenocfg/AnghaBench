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
typedef  int /*<<< orphan*/  zio_error_rank ;

/* Variables and functions */
#define  ECKSUM 130 
#define  EIO 129 
#define  ENXIO 128 

int
zio_worst_error(int e1, int e2)
{
	static int zio_error_rank[] = { 0, ENXIO, ECKSUM, EIO };
	int r1, r2;

	for (r1 = 0; r1 < sizeof (zio_error_rank) / sizeof (int); r1++)
		if (e1 == zio_error_rank[r1])
			break;

	for (r2 = 0; r2 < sizeof (zio_error_rank) / sizeof (int); r2++)
		if (e2 == zio_error_rank[r2])
			break;

	return (r1 > r2 ? e1 : e2);
}