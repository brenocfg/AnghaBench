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
 int /*<<< orphan*/  test_set_algebra ; 
 int /*<<< orphan*/  test_set_basic ; 
 int /*<<< orphan*/  test_set_empty ; 
 int /*<<< orphan*/  test_set_iter ; 

int
main (int argc, char **argv)
{
  hb_test_init (&argc, &argv);

  hb_test_add (test_set_basic);
  hb_test_add (test_set_algebra);
  hb_test_add (test_set_iter);
  hb_test_add (test_set_empty);

  return hb_test_run();
}