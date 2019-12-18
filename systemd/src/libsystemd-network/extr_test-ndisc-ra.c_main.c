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
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  test_ra () ; 
 int /*<<< orphan*/  test_radv () ; 
 int /*<<< orphan*/  test_radv_prefix () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {

        test_setup_logging(LOG_DEBUG);

        test_radv_prefix();
        test_radv();
        test_ra();

        printf("* done\n");
        return 0;
}