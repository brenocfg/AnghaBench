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
 int RARVirtualMachineRead32 (TYPE_1__*,int) ; 
 int RARVirtualMachineRead8 (TYPE_1__*,int) ; 

__attribute__((used)) static uint32_t _RARGetOperand(RARVirtualMachine *vm, uint8_t addressingmode, uint32_t value, bool bytemode)
{
    if (RARRegisterAddressingMode(0) <= addressingmode && addressingmode <= RARRegisterAddressingMode(7)) {
        uint32_t result = vm->registers[addressingmode % 8];
        if (bytemode)
            result = result & 0xFF;
        return result;
    }
    if (RARRegisterIndirectAddressingMode(0) <= addressingmode && addressingmode <= RARRegisterIndirectAddressingMode(7)) {
        if (bytemode)
            return RARVirtualMachineRead8(vm, vm->registers[addressingmode % 8]);
        return RARVirtualMachineRead32(vm, vm->registers[addressingmode % 8]);
    }
    if (RARIndexedAbsoluteAddressingMode(0) <= addressingmode && addressingmode <= RARIndexedAbsoluteAddressingMode(7)) {
        if (bytemode)
            return RARVirtualMachineRead8(vm, value + vm->registers[addressingmode % 8]);
        return RARVirtualMachineRead32(vm, value + vm->registers[addressingmode % 8]);
    }
    if (addressingmode == RARAbsoluteAddressingMode) {
        if (bytemode)
            return RARVirtualMachineRead8(vm, value);
        return RARVirtualMachineRead32(vm, value);
    }
    /* if (addressingmode == RARImmediateAddressingMode) */
    return value;
}