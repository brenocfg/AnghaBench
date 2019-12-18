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
 int /*<<< orphan*/  test_subset_glyf ; 
 int /*<<< orphan*/  test_subset_glyf_noop ; 
 int /*<<< orphan*/  test_subset_glyf_strip_hints_composite ; 
 int /*<<< orphan*/  test_subset_glyf_strip_hints_invalid ; 
 int /*<<< orphan*/  test_subset_glyf_strip_hints_simple ; 
 int /*<<< orphan*/  test_subset_glyf_with_components ; 
 int /*<<< orphan*/  test_subset_glyf_with_gsub ; 
 int /*<<< orphan*/  test_subset_glyf_without_gsub ; 

int
main (int argc, char **argv)
{
  hb_test_init (&argc, &argv);

  hb_test_add (test_subset_glyf_noop);
  hb_test_add (test_subset_glyf);
  hb_test_add (test_subset_glyf_strip_hints_simple);
  hb_test_add (test_subset_glyf_strip_hints_composite);
  hb_test_add (test_subset_glyf_strip_hints_invalid);
  hb_test_add (test_subset_glyf_with_components);
  hb_test_add (test_subset_glyf_with_gsub);
  hb_test_add (test_subset_glyf_without_gsub);

  return hb_test_run();
}