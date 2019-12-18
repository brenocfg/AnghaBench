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
typedef  int /*<<< orphan*/  MuOfficeLib ;
typedef  int MuError ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int MuOfficeLib_create (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  MuOfficeLib_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int test_async (int /*<<< orphan*/ *) ; 
 int test_sync (int /*<<< orphan*/ *) ; 

int main(int argc, char **argv)
{
	MuOfficeLib *mu;
	MuError err;
	int ret;

	err = MuOfficeLib_create(&mu);
	if (err)
	{
		fprintf(stderr, "Failed to create lib instance: error=%d\n", err);
		return EXIT_FAILURE;
	}

	ret = test_async(mu);
	if (ret)
		return ret;

	ret = test_sync(mu);
	if (ret)
		return ret;

	MuOfficeLib_destroy(mu);

	return EXIT_SUCCESS;
}