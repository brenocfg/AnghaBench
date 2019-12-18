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
typedef  int /*<<< orphan*/  zio_t ;
struct TYPE_3__ {int /*<<< orphan*/  io_abd; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  max_data_size ; 
 int /*<<< orphan*/  raidz_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ zio_bench ; 

__attribute__((used)) static void
bench_fini_raidz_maps(void)
{
	/* tear down golden zio */
	raidz_free(zio_bench.io_abd, max_data_size);
	bzero(&zio_bench, sizeof (zio_t));
}