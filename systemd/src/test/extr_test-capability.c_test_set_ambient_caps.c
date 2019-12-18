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
typedef  int /*<<< orphan*/  cap_t ;
typedef  scalar_t__ cap_flag_value_t ;

/* Variables and functions */
 int CAP_CHOWN ; 
 int /*<<< orphan*/  CAP_INHERITABLE ; 
 scalar_t__ CAP_SET ; 
 int /*<<< orphan*/  PR_CAP_AMBIENT ; 
 int /*<<< orphan*/  PR_CAP_AMBIENT_IS_SET ; 
 int UINT64_C (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  cap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_get_flag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  cap_get_proc () ; 
 int /*<<< orphan*/  capability_ambient_set_apply (int,int) ; 
 int prctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_set_ambient_caps(void) {
        cap_t caps;
        uint64_t set = 0;
        cap_flag_value_t fv;

        assert_se(prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_IS_SET, CAP_CHOWN, 0, 0) == 0);

        set = (UINT64_C(1) << CAP_CHOWN);

        assert_se(!capability_ambient_set_apply(set, true));

        caps = cap_get_proc();
        assert_se(!cap_get_flag(caps, CAP_CHOWN, CAP_INHERITABLE, &fv));
        assert(fv == CAP_SET);
        cap_free(caps);

        assert_se(prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_IS_SET, CAP_CHOWN, 0, 0) == 1);
}