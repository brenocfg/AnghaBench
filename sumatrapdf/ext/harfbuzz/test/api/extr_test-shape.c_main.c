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
 int /*<<< orphan*/  test_shape ; 
 int /*<<< orphan*/  test_shape_clusters ; 
 int /*<<< orphan*/  test_shape_list ; 

int
main (int argc, char **argv)
{
  hb_test_init (&argc, &argv);

  hb_test_add (test_shape);
  hb_test_add (test_shape_clusters);
  /* TODO test fallback shaper */
  /* TODO test shaper_full */
  hb_test_add (test_shape_list);

  return hb_test_run();
}