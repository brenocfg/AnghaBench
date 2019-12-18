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
 int IOPRIO_CLASS_BE ; 
 int IOPRIO_CLASS_IDLE ; 
 int IOPRIO_CLASS_NONE ; 
 int IOPRIO_CLASS_RT ; 
 int /*<<< orphan*/  test_ioprio_class_from_to_string_one (char*,int) ; 

__attribute__((used)) static void test_ioprio_class_from_to_string(void) {
        test_ioprio_class_from_to_string_one("none", IOPRIO_CLASS_NONE);
        test_ioprio_class_from_to_string_one("realtime", IOPRIO_CLASS_RT);
        test_ioprio_class_from_to_string_one("best-effort", IOPRIO_CLASS_BE);
        test_ioprio_class_from_to_string_one("idle", IOPRIO_CLASS_IDLE);
        test_ioprio_class_from_to_string_one("0", 0);
        test_ioprio_class_from_to_string_one("1", 1);
        test_ioprio_class_from_to_string_one("7", 7);
        test_ioprio_class_from_to_string_one("8", 8);
        test_ioprio_class_from_to_string_one("9", -1);
        test_ioprio_class_from_to_string_one("-1", -1);
}