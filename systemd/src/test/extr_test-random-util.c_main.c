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
 int /*<<< orphan*/  RANDOM_ALLOW_RDRAND ; 
 int /*<<< orphan*/  RANDOM_BLOCK ; 
 int /*<<< orphan*/  RANDOM_EXTEND_WITH_PSEUDO ; 
 int /*<<< orphan*/  test_genuine_random_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_pseudo_random_bytes () ; 
 int /*<<< orphan*/  test_rdrand () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, char **argv) {
        test_setup_logging(LOG_DEBUG);

        test_genuine_random_bytes(RANDOM_EXTEND_WITH_PSEUDO);
        test_genuine_random_bytes(0);
        test_genuine_random_bytes(RANDOM_BLOCK);
        test_genuine_random_bytes(RANDOM_ALLOW_RDRAND);

        test_pseudo_random_bytes();

        test_rdrand();

        return 0;
}