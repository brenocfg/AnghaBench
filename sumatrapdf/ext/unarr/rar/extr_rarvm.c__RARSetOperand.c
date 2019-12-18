#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_5__ {int* registers; } ;
typedef  TYPE_1__ RARVirtualMachine ;

/* Variables and functions */
 int RARAbsoluteAddressingMode ; 
 int RARIndexedAbsoluteAddressingMode (int) ; 
 int RARRegisterAddressingMode (int) ; 
 int RARRegisterIndirectAddressingMode (int) ; 
 int /*<<< orphan*/  RARVirtualMachineWrite32 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  RARVirtualMachineWrite8 (TYPE_1__*,int,int) ; 

__attribute__((used)) static void _RARSetOperand(RARVirtualMachine *vm, uint8_t addressingmode, uint32_t value, bool bytemode, uint32_t data)
{
    if (RARRegisterAddressingMode(0) <= addressingmode && addressingmode <= RARRegisterAddressingMode(7)) {
        if (bytemode)
            data = data & 0xFF;
        vm->registers[addressingmode % 8] = data;
    }
    else if (RARRegisterIndirectAddressingMode(0) <= addressingmode && addressingmode <= RARRegisterIndirectAddressingMode(7)) {
        if (bytemode)
            RARVirtualMachineWrite8(vm, vm->registers[addressingmode % 8], (uint8_t)data);
        else
            RARVirtualMachineWrite32(vm, vm->registers[addressingmode % 8], data);
    }
    else if (RARIndexedAbsoluteAddressingMode(0) <= addressingmode && addressingmode <= RARIndexedAbsoluteAddressingMode(7)) {
        if (bytemode)
            RARVirtualMachineWrite8(vm, value + vm->registers[addressingmode % 8], (uint8_t)data);
        else
            RARVirtualMachineWrite32(vm, value + vm->registers[addressingmode % 8], data);
    }
    else if (addressingmode == RARAbsoluteAddressingMode) {
        if (bytemode)
            RARVirtualMachineWrite8(vm, value, (uint8_t)data);
        else
            RARVirtualMachineWrite32(vm, value, data);
    }
}