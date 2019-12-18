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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SCMP_ARCH_AARCH64 ; 
 int /*<<< orphan*/  SCMP_ARCH_ARM ; 
 int /*<<< orphan*/  SCMP_ARCH_MIPS ; 
 int /*<<< orphan*/  SCMP_ARCH_MIPS64 ; 
 int /*<<< orphan*/  SCMP_ARCH_MIPS64N32 ; 
 int /*<<< orphan*/  SCMP_ARCH_MIPSEL ; 
 int /*<<< orphan*/  SCMP_ARCH_MIPSEL64 ; 
 int /*<<< orphan*/  SCMP_ARCH_MIPSEL64N32 ; 
 int /*<<< orphan*/  SCMP_ARCH_NATIVE ; 
 int /*<<< orphan*/  SCMP_ARCH_PPC ; 
 int /*<<< orphan*/  SCMP_ARCH_PPC64 ; 
 int /*<<< orphan*/  SCMP_ARCH_PPC64LE ; 
 int /*<<< orphan*/  SCMP_ARCH_S390 ; 
 int /*<<< orphan*/  SCMP_ARCH_S390X ; 
 int /*<<< orphan*/  SCMP_ARCH_X32 ; 
 int /*<<< orphan*/  SCMP_ARCH_X86 ; 
 int /*<<< orphan*/  SCMP_ARCH_X86_64 ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 scalar_t__ streq (char const*,char*) ; 

int seccomp_arch_from_string(const char *n, uint32_t *ret) {
        if (!n)
                return -EINVAL;

        assert(ret);

        if (streq(n, "native"))
                *ret = SCMP_ARCH_NATIVE;
        else if (streq(n, "x86"))
                *ret = SCMP_ARCH_X86;
        else if (streq(n, "x86-64"))
                *ret = SCMP_ARCH_X86_64;
        else if (streq(n, "x32"))
                *ret = SCMP_ARCH_X32;
        else if (streq(n, "arm"))
                *ret = SCMP_ARCH_ARM;
        else if (streq(n, "arm64"))
                *ret = SCMP_ARCH_AARCH64;
        else if (streq(n, "mips"))
                *ret = SCMP_ARCH_MIPS;
        else if (streq(n, "mips64"))
                *ret = SCMP_ARCH_MIPS64;
        else if (streq(n, "mips64-n32"))
                *ret = SCMP_ARCH_MIPS64N32;
        else if (streq(n, "mips-le"))
                *ret = SCMP_ARCH_MIPSEL;
        else if (streq(n, "mips64-le"))
                *ret = SCMP_ARCH_MIPSEL64;
        else if (streq(n, "mips64-le-n32"))
                *ret = SCMP_ARCH_MIPSEL64N32;
        else if (streq(n, "ppc"))
                *ret = SCMP_ARCH_PPC;
        else if (streq(n, "ppc64"))
                *ret = SCMP_ARCH_PPC64;
        else if (streq(n, "ppc64-le"))
                *ret = SCMP_ARCH_PPC64LE;
        else if (streq(n, "s390"))
                *ret = SCMP_ARCH_S390;
        else if (streq(n, "s390x"))
                *ret = SCMP_ARCH_S390X;
        else
                return -EINVAL;

        return 0;
}