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
typedef  int uint64_t ;
typedef  int cap_t ;
typedef  scalar_t__ cap_flag_value_t ;

/* Variables and functions */
 int CAP_CHOWN ; 
 int /*<<< orphan*/  CAP_INHERITABLE ; 
 scalar_t__ CAP_SET ; 
 int UINT64_C (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  cap_free (int) ; 
 int /*<<< orphan*/  cap_get_flag (int,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int cap_get_proc () ; 
 int /*<<< orphan*/  capability_update_inherited_set (int,int) ; 

__attribute__((used)) static void test_update_inherited_set(void) {
        cap_t caps;
        uint64_t set = 0;
        cap_flag_value_t fv;

        caps = cap_get_proc();
        assert_se(caps);

        set = (UINT64_C(1) << CAP_CHOWN);

        assert_se(!capability_update_inherited_set(caps, set));
        assert_se(!cap_get_flag(caps, CAP_CHOWN, CAP_INHERITABLE, &fv));
        assert(fv == CAP_SET);

        cap_free(caps);
}