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
typedef  int /*<<< orphan*/  raidz_test_opts_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  print_opts (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rto_opts ; 
 int run_gen_check (int /*<<< orphan*/ *) ; 
 int run_rec_check (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
run_test(raidz_test_opts_t *opts)
{
	int err = 0;

	if (opts == NULL)
		opts = &rto_opts;

	print_opts(opts, B_FALSE);

	err |= run_gen_check(opts);
	err |= run_rec_check(opts);

	return (err);
}