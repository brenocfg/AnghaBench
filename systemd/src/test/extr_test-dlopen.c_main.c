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
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  RTLD_NOW ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ dlclose (void*) ; 
 void* dlopen (char*,int /*<<< orphan*/ ) ; 

int main(int argc, char **argv) {
        void *handle;

        assert_se(handle = dlopen(argv[1], RTLD_NOW));
        assert_se(dlclose(handle) == 0);

        return EXIT_SUCCESS;
}