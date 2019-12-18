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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ scmp_filter_ctx ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SCMP_ACT_ALLOW ; 
 int /*<<< orphan*/  SCMP_ARCH_NATIVE ; 
 int /*<<< orphan*/  SCMP_FLTATR_ACT_BADARCH ; 
 int /*<<< orphan*/  SCMP_FLTATR_CTL_NNP ; 
 int /*<<< orphan*/  assert (int) ; 
 int seccomp_arch_add (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ seccomp_arch_exist (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seccomp_arch_native () ; 
 int seccomp_arch_remove (scalar_t__,int /*<<< orphan*/ ) ; 
 int seccomp_attr_set (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ seccomp_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seccomp_release (scalar_t__) ; 

int seccomp_init_for_arch(scmp_filter_ctx *ret, uint32_t arch, uint32_t default_action) {
        scmp_filter_ctx seccomp;
        int r;

        /* Much like seccomp_init(), but initializes the filter for one specific architecture only, without affecting
         * any others. Also, turns off the NNP fiddling. */

        seccomp = seccomp_init(default_action);
        if (!seccomp)
                return -ENOMEM;

        if (arch != SCMP_ARCH_NATIVE &&
            arch != seccomp_arch_native()) {

                r = seccomp_arch_remove(seccomp, seccomp_arch_native());
                if (r < 0)
                        goto finish;

                r = seccomp_arch_add(seccomp, arch);
                if (r < 0)
                        goto finish;

                assert(seccomp_arch_exist(seccomp, arch) >= 0);
                assert(seccomp_arch_exist(seccomp, SCMP_ARCH_NATIVE) == -EEXIST);
                assert(seccomp_arch_exist(seccomp, seccomp_arch_native()) == -EEXIST);
        } else {
                assert(seccomp_arch_exist(seccomp, SCMP_ARCH_NATIVE) >= 0);
                assert(seccomp_arch_exist(seccomp, seccomp_arch_native()) >= 0);
        }

        r = seccomp_attr_set(seccomp, SCMP_FLTATR_ACT_BADARCH, SCMP_ACT_ALLOW);
        if (r < 0)
                goto finish;

        r = seccomp_attr_set(seccomp, SCMP_FLTATR_CTL_NNP, 0);
        if (r < 0)
                goto finish;

        *ret = seccomp;
        return 0;

finish:
        seccomp_release(seccomp);
        return r;
}