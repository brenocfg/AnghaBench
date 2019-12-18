#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long uint64_t ;
typedef  scalar_t__ hrtime_t ;
struct TYPE_5__ {int rto_dcols; } ;
struct TYPE_4__ {unsigned long long io_size; } ;

/* Variables and functions */
 unsigned long long BENCH_ASHIFT ; 
 int /*<<< orphan*/  D_ALL ; 
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,unsigned long long,unsigned long long,double,double,unsigned int) ; 
 unsigned long long MAX_CS_SHIFT ; 
 int MIN (int,scalar_t__) ; 
 unsigned long long MIN_CS_SHIFT ; 
 double NSEC2SEC (double) ; 
 int PARITY_PQR ; 
 int RAIDZ_REC_NUM ; 
 unsigned long long REC_BENCH_MEMORY ; 
 scalar_t__ gethrtime () ; 
 scalar_t__ raidz_ncols (int /*<<< orphan*/ ) ; 
 scalar_t__ raidz_parity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * raidz_rec_name ; 
 int /*<<< orphan*/  rm_bench ; 
 TYPE_3__ rto_opts ; 
 int /*<<< orphan*/  vdev_raidz_map_alloc (TYPE_1__*,unsigned long long,int,int) ; 
 int /*<<< orphan*/  vdev_raidz_map_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_raidz_reconstruct (int /*<<< orphan*/ ,int const*,int) ; 
 TYPE_1__ zio_bench ; 

__attribute__((used)) static void
run_rec_bench_impl(const char *impl)
{
	int fn, ncols, nbad;
	uint64_t ds, iter_cnt, iter, disksize;
	hrtime_t start;
	double elapsed, d_bw;
	static const int tgt[7][3] = {
		{1, 2, 3},	/* rec_p:   bad QR & D[0]	*/
		{0, 2, 3},	/* rec_q:   bad PR & D[0]	*/
		{0, 1, 3},	/* rec_r:   bad PQ & D[0]	*/
		{2, 3, 4},	/* rec_pq:  bad R  & D[0][1]	*/
		{1, 3, 4},	/* rec_pr:  bad Q  & D[0][1]	*/
		{0, 3, 4},	/* rec_qr:  bad P  & D[0][1]	*/
		{3, 4, 5}	/* rec_pqr: bad    & D[0][1][2] */
	};

	for (fn = 0; fn < RAIDZ_REC_NUM; fn++) {
		for (ds = MIN_CS_SHIFT; ds <= MAX_CS_SHIFT; ds++) {

			/* create suitable raidz_map */
			ncols = rto_opts.rto_dcols + PARITY_PQR;
			zio_bench.io_size = 1ULL << ds;

			/*
			 * raidz block is too short to test
			 * the requested method
			 */
			if (zio_bench.io_size / rto_opts.rto_dcols <
			    (1ULL << BENCH_ASHIFT))
				continue;

			rm_bench = vdev_raidz_map_alloc(&zio_bench,
			    BENCH_ASHIFT, ncols, PARITY_PQR);

			/* estimate iteration count */
			iter_cnt = (REC_BENCH_MEMORY);
			iter_cnt /= zio_bench.io_size;

			/* calculate how many bad columns there are */
			nbad = MIN(3, raidz_ncols(rm_bench) -
			    raidz_parity(rm_bench));

			start = gethrtime();
			for (iter = 0; iter < iter_cnt; iter++)
				vdev_raidz_reconstruct(rm_bench, tgt[fn], nbad);
			elapsed = NSEC2SEC((double)(gethrtime() - start));

			disksize = (1ULL << ds) / rto_opts.rto_dcols;
			d_bw = (double)iter_cnt * (double)(disksize);
			d_bw /= (1024.0 * 1024.0 * elapsed);

			LOG(D_ALL, "%10s, %8s, %zu, %10llu, %lf, %lf, %u\n",
			    impl,
			    raidz_rec_name[fn],
			    rto_opts.rto_dcols,
			    (1ULL<<ds),
			    d_bw,
			    d_bw * (double)ncols,
			    (unsigned)iter_cnt);

			vdev_raidz_map_free(rm_bench);
		}
	}
}