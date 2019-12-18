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
typedef  int uint32_t ;

/* Variables and functions */
#define  SCMP_ARCH_AARCH64 144 
#define  SCMP_ARCH_ARM 143 
#define  SCMP_ARCH_MIPS 142 
#define  SCMP_ARCH_MIPS64 141 
#define  SCMP_ARCH_MIPS64N32 140 
#define  SCMP_ARCH_MIPSEL 139 
#define  SCMP_ARCH_MIPSEL64 138 
#define  SCMP_ARCH_MIPSEL64N32 137 
#define  SCMP_ARCH_NATIVE 136 
#define  SCMP_ARCH_PPC 135 
#define  SCMP_ARCH_PPC64 134 
#define  SCMP_ARCH_PPC64LE 133 
#define  SCMP_ARCH_S390 132 
#define  SCMP_ARCH_S390X 131 
#define  SCMP_ARCH_X32 130 
#define  SCMP_ARCH_X86 129 
#define  SCMP_ARCH_X86_64 128 

const char* seccomp_arch_to_string(uint32_t c) {
        /* Maintain order used in <seccomp.h>.
         *
         * Names used here should be the same as those used for ConditionArchitecture=,
         * except for "subarchitectures" like x32. */

        switch(c) {
        case SCMP_ARCH_NATIVE:
                return "native";
        case SCMP_ARCH_X86:
                return "x86";
        case SCMP_ARCH_X86_64:
                return "x86-64";
        case SCMP_ARCH_X32:
                return "x32";
        case SCMP_ARCH_ARM:
                return "arm";
        case SCMP_ARCH_AARCH64:
                return "arm64";
        case SCMP_ARCH_MIPS:
                return "mips";
        case SCMP_ARCH_MIPS64:
                return "mips64";
        case SCMP_ARCH_MIPS64N32:
                return "mips64-n32";
        case SCMP_ARCH_MIPSEL:
                return "mips-le";
        case SCMP_ARCH_MIPSEL64:
                return "mips64-le";
        case SCMP_ARCH_MIPSEL64N32:
                return "mips64-le-n32";
        case SCMP_ARCH_PPC:
                return "ppc";
        case SCMP_ARCH_PPC64:
                return "ppc64";
        case SCMP_ARCH_PPC64LE:
                return "ppc64-le";
        case SCMP_ARCH_S390:
                return "s390";
        case SCMP_ARCH_S390X:
                return "s390x";
        default:
                return NULL;
        }
}