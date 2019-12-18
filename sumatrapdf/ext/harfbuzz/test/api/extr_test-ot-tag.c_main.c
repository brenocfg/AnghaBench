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
 int /*<<< orphan*/  test_ot_tag_language ; 
 int /*<<< orphan*/  test_ot_tag_script_degenerate ; 
 int /*<<< orphan*/  test_ot_tag_script_indic ; 
 int /*<<< orphan*/  test_ot_tag_script_simple ; 

int
main (int argc, char **argv)
{
  hb_test_init (&argc, &argv);

  hb_test_add (test_ot_tag_script_degenerate);
  hb_test_add (test_ot_tag_script_simple);
  hb_test_add (test_ot_tag_script_indic);

  hb_test_add (test_ot_tag_language);

  return hb_test_run();
}