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
 int NELEMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  icp_fini () ; 
 int /*<<< orphan*/  icp_init () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int run_test (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * test_vectors ; 

int
main(int argc, char **argv)
{
	int ret, i;

	icp_init();

	for (i = 0; i < NELEMS(test_vectors); i++) {
		ret = run_test(i, &test_vectors[i]);
		if (ret != 0)
			break;
	}

	icp_fini();

	if (ret == 0) {
		printf("All tests passed successfully.\n");
		return (0);
	} else {
		printf("Test failed.\n");
		return (1);
	}
}