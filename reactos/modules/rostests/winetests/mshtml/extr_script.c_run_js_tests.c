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
 scalar_t__ is_ie9plus ; 
 int /*<<< orphan*/  run_js_script (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void run_js_tests(void)
{
    run_js_script("jstest.html");
    run_js_script("exectest.html");
    run_js_script("vbtest.html");
    run_js_script("events.html");
    if(is_ie9plus)
        run_js_script("nav_test.html");
    else
        win_skip("Skipping nav_test.html on IE older than 9 (for broken ieframe onload).\n");
}