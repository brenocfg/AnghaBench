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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  dump_nvlist (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvlist_lookup_nvlist (int /*<<< orphan*/ *,char*) ; 
 int lzc_channel_program (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * nvl ; 
 int /*<<< orphan*/  nvlist_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pool ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  unexpected_failures ; 

__attribute__((used)) static void
test(const char *testname, boolean_t expect_success, boolean_t expect_match)
{
	char *progstr = "input = ...; return {output=input}";

	nvlist_t *outnvl;

	(void) printf("\nrunning test '%s'; input:\n", testname);
	dump_nvlist(nvl, 4);

	int err = lzc_channel_program(pool, progstr,
	    10 * 1000 * 1000, 10 * 1024 * 1024, nvl, &outnvl);

	(void) printf("lzc_channel_program returned %u\n", err);
	dump_nvlist(outnvl, 5);

	if (err == 0 && expect_match) {
		/*
		 * Verify that outnvl is the same as input nvl, if we expect
		 * them to be. The input and output will never match if the
		 * input contains an array (since arrays are converted to lua
		 * tables), so this is only asserted for some test cases.
		 */
		nvlist_t *real_outnvl = fnvlist_lookup_nvlist(outnvl, "return");
		real_outnvl = fnvlist_lookup_nvlist(real_outnvl, "output");
		if (!nvlist_equal(nvl, real_outnvl)) {
			unexpected_failures = B_TRUE;
			(void) printf("unexpected input/output mismatch for "
			    "case: %s\n", testname);
		}
	}
	if (err != 0 && expect_success) {
		unexpected_failures = B_TRUE;
		(void) printf("unexpected FAIL of case: %s\n", testname);
	}

	fnvlist_free(nvl);
	nvl = fnvlist_alloc();
}