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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int CV_ARM64_FP ; 
 int CV_ARM64_LR ; 
 int CV_ARM64_NOREG ; 
 int CV_ARM64_SP ; 
 int CV_ARM64_X0 ; 
 int /*<<< orphan*/  FIXME (char*,unsigned int) ; 

__attribute__((used)) static unsigned arm64_map_dwarf_register(unsigned regno, BOOL eh_frame)
{
    if (regno <= 28) return CV_ARM64_X0 + regno;
    if (regno == 29) return CV_ARM64_FP;
    if (regno == 30) return CV_ARM64_LR;
    if (regno == 31) return CV_ARM64_SP;

    FIXME("Don't know how to map register %d\n", regno);
    return CV_ARM64_NOREG;
}