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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 scalar_t__ coredump_vacuum (int,int /*<<< orphan*/ ,int) ; 

int main(int argc, char *argv[]) {

        if (coredump_vacuum(-1, (uint64_t) -1, 70 * 1024) < 0)
                return EXIT_FAILURE;

        return EXIT_SUCCESS;
}