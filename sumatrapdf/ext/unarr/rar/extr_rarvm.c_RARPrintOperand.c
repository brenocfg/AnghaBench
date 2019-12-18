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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int RARAbsoluteAddressingMode ; 
 int RARImmediateAddressingMode ; 
 int RARIndexedAbsoluteAddressingMode (int) ; 
 int RARRegisterAddressingMode (int) ; 
 int RARRegisterIndirectAddressingMode (int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static void RARPrintOperand(uint8_t addressingmode, uint32_t value)
{
    if (RARRegisterAddressingMode(0) <= addressingmode && addressingmode <= RARRegisterAddressingMode(7))
        printf("r%d", addressingmode % 8);
    else if (RARRegisterIndirectAddressingMode(0) <= addressingmode && addressingmode <= RARRegisterIndirectAddressingMode(7))
        printf("@(r%d)", addressingmode % 8);
    else if (RARIndexedAbsoluteAddressingMode(0) <= addressingmode && addressingmode <= RARIndexedAbsoluteAddressingMode(7))
        printf("@(r%d+$%02x)", addressingmode % 8, value);
    else if (addressingmode == RARAbsoluteAddressingMode)
        printf("@($%02x)", value);
    else if (addressingmode == RARImmediateAddressingMode)
        printf("$%02x", value);
}