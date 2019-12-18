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
 int /*<<< orphan*/  hb_test_add (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_test_init (int*,char***) ; 
 int hb_test_run () ; 
 int /*<<< orphan*/  test_subset_hmtx_decrease_num_metrics ; 
 int /*<<< orphan*/  test_subset_hmtx_keep_num_metrics ; 
 int /*<<< orphan*/  test_subset_hmtx_monospace ; 
 int /*<<< orphan*/  test_subset_hmtx_noop ; 
 int /*<<< orphan*/  test_subset_hmtx_simple_subset ; 
 int /*<<< orphan*/  test_subset_invalid_hmtx ; 

int
main (int argc, char **argv)
{
  hb_test_init (&argc, &argv);

  hb_test_add (test_subset_hmtx_simple_subset);
  hb_test_add (test_subset_hmtx_monospace);
  hb_test_add (test_subset_hmtx_keep_num_metrics);
  hb_test_add (test_subset_hmtx_decrease_num_metrics);
  hb_test_add (test_subset_hmtx_noop);
  hb_test_add (test_subset_invalid_hmtx);

  return hb_test_run();
}