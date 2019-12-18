#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * memory; } ;
typedef  TYPE_1__ RARVirtualMachine ;

/* Variables and functions */
 size_t RARProgramMemoryMask ; 

void RARVirtualMachineWrite8(RARVirtualMachine *vm, uint32_t address, uint8_t val)
{
    vm->memory[address & RARProgramMemoryMask] = val;
}