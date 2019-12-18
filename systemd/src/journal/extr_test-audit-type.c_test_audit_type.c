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
 int AUDIT_KERNEL ; 
 int /*<<< orphan*/  print_audit_label (int) ; 

__attribute__((used)) static void test_audit_type(void) {
        int i;

        for (i = 0; i <= AUDIT_KERNEL; i++)
                print_audit_label(i);
}