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
 int /*<<< orphan*/  check_quirks_mode ; 
 int /*<<< orphan*/  check_strict_mode ; 
 int /*<<< orphan*/  run_domtest (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_quirks_mode_offsetHeight ; 

__attribute__((used)) static void test_quirks_mode(void)
{
    run_domtest("<html></html>", check_quirks_mode);
    run_domtest("<!DOCTYPE html>\n<html></html>", check_strict_mode);
    run_domtest("<!-- comment --><!DOCTYPE html>\n<html></html>", check_quirks_mode);
    run_domtest("<html><body></body></html>", test_quirks_mode_offsetHeight);
}