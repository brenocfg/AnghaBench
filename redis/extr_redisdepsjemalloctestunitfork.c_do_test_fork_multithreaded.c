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
typedef  int /*<<< orphan*/  thd_t ;

/* Variables and functions */
 int /*<<< orphan*/  do_fork_thd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thd_create (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thd_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
do_test_fork_multithreaded() {
	thd_t child;
	thd_create(&child, do_fork_thd, NULL);
	do_fork_thd(NULL);
	thd_join(child, NULL);
}