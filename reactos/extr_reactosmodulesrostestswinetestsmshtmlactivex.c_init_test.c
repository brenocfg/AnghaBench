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
 int TEST_DISPONLY ; 
 int TEST_NOQUICKACT ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ activex_refcnt ; 
 int /*<<< orphan*/  have_container ; 
 int no_quickact ; 
 int plugin_behavior ; 

__attribute__((used)) static void init_test(int behavior)
{
    plugin_behavior = behavior;

    activex_refcnt = 0;
    no_quickact = behavior == TEST_NOQUICKACT || behavior == TEST_DISPONLY;
    have_container = TRUE;
}