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
 int /*<<< orphan*/  test_block_signals () ; 
 int /*<<< orphan*/  test_ignore_signals () ; 
 int /*<<< orphan*/  test_rt_signals () ; 
 int /*<<< orphan*/  test_signal_from_string () ; 

int main(int argc, char *argv[]) {
        test_rt_signals();
        test_signal_from_string();
        test_block_signals();
        test_ignore_signals();

        return 0;
}