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
 int /*<<< orphan*/  test_types_direction ; 
 int /*<<< orphan*/  test_types_int ; 
 int /*<<< orphan*/  test_types_language ; 
 int /*<<< orphan*/  test_types_script ; 
 int /*<<< orphan*/  test_types_tag ; 

int
main (int argc, char **argv)
{
  hb_test_init (&argc, &argv);

  hb_test_add (test_types_int);
  hb_test_add (test_types_direction);
  hb_test_add (test_types_tag);
  hb_test_add (test_types_script);
  hb_test_add (test_types_language);

  return hb_test_run();
}