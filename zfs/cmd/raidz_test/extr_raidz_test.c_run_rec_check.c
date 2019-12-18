#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_t ;
struct TYPE_6__ {int /*<<< orphan*/ * rm_golden; int /*<<< orphan*/ * zio_golden; } ;
typedef  TYPE_1__ raidz_test_opts_t ;
typedef  int /*<<< orphan*/  raidz_map_t ;

/* Variables and functions */
 char* DBLSEP ; 
 int /*<<< orphan*/  D_INFO ; 
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  PARITY_PQR ; 
 unsigned int RAIDZ_REC_NUM ; 
 char* SEP ; 
 int /*<<< orphan*/  fini_raidz_map (int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 unsigned int init_raidz_golden_map (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * init_raidz_map (TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ raidz_impl_names ; 
 int /*<<< orphan*/ * raidz_rec_name ; 
 scalar_t__ run_rec_check_impl (TYPE_1__*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  vdev_raidz_generate_parity (int /*<<< orphan*/ *) ; 
 scalar_t__ vdev_raidz_impl_set (char*) ; 

__attribute__((used)) static int
run_rec_check(raidz_test_opts_t *opts)
{
	char **impl_name;
	unsigned fn, err = 0;
	zio_t *zio_test;
	raidz_map_t *rm_test;

	err = init_raidz_golden_map(opts, PARITY_PQR);
	if (0 != err)
		return (err);

	LOG(D_INFO, DBLSEP);
	LOG(D_INFO, "Testing data reconstruction...\n");

	for (impl_name = (char **)raidz_impl_names+1; *impl_name != NULL;
	    impl_name++) {

		LOG(D_INFO, SEP);
		LOG(D_INFO, "\tTesting [%s] implementation...", *impl_name);

		if (vdev_raidz_impl_set(*impl_name) != 0) {
			LOG(D_INFO, "[SKIP]\n");
			continue;
		} else
			LOG(D_INFO, "[SUPPORTED]\n");


		/* create suitable raidz_map */
		rm_test = init_raidz_map(opts, &zio_test, PARITY_PQR);
		/* generate parity */
		vdev_raidz_generate_parity(rm_test);

		for (fn = 0; fn < RAIDZ_REC_NUM; fn++) {

			LOG(D_INFO, "\t\tTesting method [%s] ...",
			    raidz_rec_name[fn]);

			if (run_rec_check_impl(opts, rm_test, fn) != 0) {
				LOG(D_INFO, "[FAIL]\n");
				err++;

			} else
				LOG(D_INFO, "[PASS]\n");

		}
		/* tear down test raidz_map */
		fini_raidz_map(&zio_test, &rm_test);
	}

	fini_raidz_map(&opts->zio_golden, &opts->rm_golden);

	return (err);
}