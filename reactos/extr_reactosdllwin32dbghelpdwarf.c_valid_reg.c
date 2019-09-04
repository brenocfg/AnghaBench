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
typedef  scalar_t__ ULONG_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,scalar_t__) ; 
 scalar_t__ NB_FRAME_REGS ; 

__attribute__((used)) static int valid_reg(ULONG_PTR reg)
{
    if (reg >= NB_FRAME_REGS) FIXME("unsupported reg %lx\n", reg);
    return (reg < NB_FRAME_REGS);
}