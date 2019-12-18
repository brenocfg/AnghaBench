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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct MemBitReader {int /*<<< orphan*/  at_eof; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARAbsoluteAddressingMode ; 
 int /*<<< orphan*/  RARImmediateAddressingMode ; 
 int /*<<< orphan*/  RARIndexedAbsoluteAddressingMode (int /*<<< orphan*/ ) ; 
 scalar_t__ RARInstructionIsRelativeJump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RARRegisterAddressingMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RARRegisterIndirectAddressingMode (int /*<<< orphan*/ ) ; 
 scalar_t__ br_bits (struct MemBitReader*,int) ; 
 scalar_t__ br_next_rarvm_number (struct MemBitReader*) ; 

__attribute__((used)) static bool rar_parse_operand(struct MemBitReader *br, uint8_t instruction, bool bytemode, uint32_t instrcount, uint8_t *addressmode, uint32_t *value)
{
    if (br_bits(br, 1)) {
        *addressmode = RARRegisterAddressingMode((uint8_t)br_bits(br, 3));
        *value = 0;
    }
    else if (br_bits(br, 1)) {
        if (br_bits(br, 1)) {
            if (br_bits(br, 1))
                *addressmode = RARAbsoluteAddressingMode;
            else
                *addressmode = RARIndexedAbsoluteAddressingMode((uint8_t)br_bits(br, 3));
            *value = br_next_rarvm_number(br);
        }
        else {
            *addressmode = RARRegisterIndirectAddressingMode((uint8_t)br_bits(br, 3));
            *value = 0;
        }
    }
    else {
        *addressmode = RARImmediateAddressingMode;
        if (!bytemode)
            *value = br_next_rarvm_number(br);
        else
            *value = br_bits(br, 8);
        if (instrcount != (uint32_t)-1 && RARInstructionIsRelativeJump(instruction)) {
            if (*value >= 256) /* absolute address */
                *value -= 256;
            else { /* relative address */
                if (*value >= 136)
                    *value -= 264;
                else if (*value >= 16)
                    *value -= 8;
                else if (*value >= 8)
                    *value -= 16;
                *value += instrcount;
            }
        }
    }
    return !br->at_eof;
}