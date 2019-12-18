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
 int /*<<< orphan*/  test_subset_hdmx_fails_sanitize ; 
 int /*<<< orphan*/  test_subset_hdmx_invalid ; 
 int /*<<< orphan*/  test_subset_hdmx_multiple_device_records ; 
 int /*<<< orphan*/  test_subset_hdmx_noop ; 
 int /*<<< orphan*/  test_subset_hdmx_simple_subset ; 

int
main (int argc, char **argv)
{
  hb_test_init (&argc, &argv);

  hb_test_add (test_subset_hdmx_simple_subset);
  hb_test_add (test_subset_hdmx_multiple_device_records);
  hb_test_add (test_subset_hdmx_invalid);
  hb_test_add (test_subset_hdmx_fails_sanitize);
  hb_test_add (test_subset_hdmx_noop);

  return hb_test_run();
}