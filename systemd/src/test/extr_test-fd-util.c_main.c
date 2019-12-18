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
 int /*<<< orphan*/  test_acquire_data_fd () ; 
 int /*<<< orphan*/  test_close_many () ; 
 int /*<<< orphan*/  test_close_nointr () ; 
 int /*<<< orphan*/  test_fd_duplicate_data_fd () ; 
 int /*<<< orphan*/  test_fd_move_above_stdio () ; 
 int /*<<< orphan*/  test_open_serialization_fd () ; 
 int /*<<< orphan*/  test_read_nr_open () ; 
 int /*<<< orphan*/  test_rearrange_stdio () ; 
 int /*<<< orphan*/  test_same_fd () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {

        test_setup_logging(LOG_DEBUG);

        test_close_many();
        test_close_nointr();
        test_same_fd();
        test_open_serialization_fd();
        test_acquire_data_fd();
        test_fd_move_above_stdio();
        test_rearrange_stdio();
        test_fd_duplicate_data_fd();
        test_read_nr_open();

        return 0;
}