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
 int EINVAL ; 
 int /*<<< orphan*/  test_rename_process_multi () ; 
 int /*<<< orphan*/  test_rename_process_one (char*,int) ; 

__attribute__((used)) static void test_rename_process(void) {
        test_rename_process_one(NULL, -EINVAL);
        test_rename_process_one("", -EINVAL);
        test_rename_process_one("foo", 1); /* should always fit */
        test_rename_process_one("this is a really really long process name, followed by some more words", 0); /* unlikely to fit */
        test_rename_process_one("1234567", 1); /* should always fit */
        test_rename_process_multi(); /* multiple invocations and dropped privileges */
}