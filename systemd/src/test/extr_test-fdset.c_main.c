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
 int /*<<< orphan*/  test_fdset_cloexec () ; 
 int /*<<< orphan*/  test_fdset_close_others () ; 
 int /*<<< orphan*/  test_fdset_isempty () ; 
 int /*<<< orphan*/  test_fdset_iterate () ; 
 int /*<<< orphan*/  test_fdset_new_array () ; 
 int /*<<< orphan*/  test_fdset_new_fill () ; 
 int /*<<< orphan*/  test_fdset_put_dup () ; 
 int /*<<< orphan*/  test_fdset_remove () ; 
 int /*<<< orphan*/  test_fdset_steal_first () ; 

int main(int argc, char *argv[]) {
        test_fdset_new_fill();
        test_fdset_put_dup();
        test_fdset_cloexec();
        test_fdset_close_others();
        test_fdset_remove();
        test_fdset_iterate();
        test_fdset_isempty();
        test_fdset_steal_first();
        test_fdset_new_array();

        return 0;
}