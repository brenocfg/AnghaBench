#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tgtidx ;
struct TYPE_11__ {int rto_dcols; int /*<<< orphan*/  rto_sanity; } ;
typedef  TYPE_1__ raidz_test_opts_t ;
struct TYPE_12__ {int rm_cols; } ;
typedef  TYPE_2__ raidz_map_t ;
struct TYPE_13__ {scalar_t__ rto_should_stop; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_DEBUG ; 
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*,int,...) ; 
 int const RAIDZ_REC_PQ ; 
 int const RAIDZ_REC_PQR ; 
 scalar_t__ cmp_data (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  corrupt_colums (TYPE_2__*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int raidz_parity (TYPE_2__*) ; 
 TYPE_6__ rto_opts ; 
 int /*<<< orphan*/  vdev_raidz_reconstruct (TYPE_2__*,int*,int) ; 

__attribute__((used)) static int
run_rec_check_impl(raidz_test_opts_t *opts, raidz_map_t *rm, const int fn)
{
	int x0, x1, x2;
	int tgtidx[3];
	int err = 0;
	static const int rec_tgts[7][3] = {
		{1, 2, 3},	/* rec_p:   bad QR & D[0]	*/
		{0, 2, 3},	/* rec_q:   bad PR & D[0]	*/
		{0, 1, 3},	/* rec_r:   bad PQ & D[0]	*/
		{2, 3, 4},	/* rec_pq:  bad R  & D[0][1]	*/
		{1, 3, 4},	/* rec_pr:  bad Q  & D[0][1]	*/
		{0, 3, 4},	/* rec_qr:  bad P  & D[0][1]	*/
		{3, 4, 5}	/* rec_pqr: bad    & D[0][1][2] */
	};

	memcpy(tgtidx, rec_tgts[fn], sizeof (tgtidx));

	if (fn < RAIDZ_REC_PQ) {
		/* can reconstruct 1 failed data disk */
		for (x0 = 0; x0 < opts->rto_dcols; x0++) {
			if (x0 >= rm->rm_cols - raidz_parity(rm))
				continue;

			/* Check if should stop */
			if (rto_opts.rto_should_stop)
				return (err);

			LOG(D_DEBUG, "[%d] ", x0);

			tgtidx[2] = x0 + raidz_parity(rm);

			corrupt_colums(rm, tgtidx+2, 1);

			if (!opts->rto_sanity)
				vdev_raidz_reconstruct(rm, tgtidx, 3);

			if (cmp_data(opts, rm) != 0) {
				err++;
				LOG(D_DEBUG, "\nREC D[%d]... [FAIL]\n", x0);
			}
		}

	} else if (fn < RAIDZ_REC_PQR) {
		/* can reconstruct 2 failed data disk */
		for (x0 = 0; x0 < opts->rto_dcols; x0++) {
			if (x0 >= rm->rm_cols - raidz_parity(rm))
				continue;
			for (x1 = x0 + 1; x1 < opts->rto_dcols; x1++) {
				if (x1 >= rm->rm_cols - raidz_parity(rm))
					continue;

				/* Check if should stop */
				if (rto_opts.rto_should_stop)
					return (err);

				LOG(D_DEBUG, "[%d %d] ", x0, x1);

				tgtidx[1] = x0 + raidz_parity(rm);
				tgtidx[2] = x1 + raidz_parity(rm);

				corrupt_colums(rm, tgtidx+1, 2);

				if (!opts->rto_sanity)
					vdev_raidz_reconstruct(rm, tgtidx, 3);

				if (cmp_data(opts, rm) != 0) {
					err++;
					LOG(D_DEBUG, "\nREC D[%d %d]... "
					    "[FAIL]\n", x0, x1);
				}
			}
		}
	} else {
		/* can reconstruct 3 failed data disk */
		for (x0 = 0; x0 < opts->rto_dcols; x0++) {
			if (x0 >= rm->rm_cols - raidz_parity(rm))
				continue;
			for (x1 = x0 + 1; x1 < opts->rto_dcols; x1++) {
				if (x1 >= rm->rm_cols - raidz_parity(rm))
					continue;
				for (x2 = x1 + 1; x2 < opts->rto_dcols; x2++) {
					if (x2 >=
					    rm->rm_cols - raidz_parity(rm))
						continue;

					/* Check if should stop */
					if (rto_opts.rto_should_stop)
						return (err);

					LOG(D_DEBUG, "[%d %d %d]", x0, x1, x2);

					tgtidx[0] = x0 + raidz_parity(rm);
					tgtidx[1] = x1 + raidz_parity(rm);
					tgtidx[2] = x2 + raidz_parity(rm);

					corrupt_colums(rm, tgtidx, 3);

					if (!opts->rto_sanity)
						vdev_raidz_reconstruct(rm,
						    tgtidx, 3);

					if (cmp_data(opts, rm) != 0) {
						err++;
						LOG(D_DEBUG,
						    "\nREC D[%d %d %d]... "
						    "[FAIL]\n", x0, x1, x2);
					}
				}
			}
		}
	}
	return (err);
}