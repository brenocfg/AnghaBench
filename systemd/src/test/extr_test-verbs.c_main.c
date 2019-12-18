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
 int /*<<< orphan*/  test_verbs () ; 
 int /*<<< orphan*/  test_verbs_no_default () ; 

int main(int argc, char *argv[]) {
        test_verbs();
        test_verbs_no_default();

        return 0;
}