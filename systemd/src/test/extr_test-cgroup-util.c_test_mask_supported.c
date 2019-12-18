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
typedef  int CGroupMask ;
typedef  scalar_t__ CGroupController ;

/* Variables and functions */
 int CGROUP_CONTROLLER_TO_MASK (scalar_t__) ; 
 scalar_t__ _CGROUP_CONTROLLER_MAX ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ cg_mask_supported (int*) ; 
 char* cgroup_controller_to_string (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 char* yes_no (int) ; 

__attribute__((used)) static void test_mask_supported(void) {

        CGroupMask m;
        CGroupController c;

        assert_se(cg_mask_supported(&m) >= 0);

        for (c = 0; c < _CGROUP_CONTROLLER_MAX; c++)
                printf("'%s' is supported: %s\n", cgroup_controller_to_string(c), yes_no(m & CGROUP_CONTROLLER_TO_MASK(c)));
}