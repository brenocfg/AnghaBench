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
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  test_cescape () ; 
 int /*<<< orphan*/  test_cunescape () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_shell_escape () ; 
 int /*<<< orphan*/  test_shell_maybe_quote () ; 
 int /*<<< orphan*/  test_xescape () ; 
 int /*<<< orphan*/  test_xescape_full (int) ; 

int main(int argc, char *argv[]) {
        test_setup_logging(LOG_DEBUG);

        test_cescape();
        test_xescape();
        test_xescape_full(false);
        test_xescape_full(true);
        test_cunescape();
        test_shell_escape();
        test_shell_maybe_quote();

        return 0;
}