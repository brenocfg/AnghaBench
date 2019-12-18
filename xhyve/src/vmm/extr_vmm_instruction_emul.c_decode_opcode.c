#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_2__ {scalar_t__ op_type; } ;
struct vie {TYPE_1__ op; } ;

/* Variables and functions */
 scalar_t__ VIE_OP_TYPE_NONE ; 
 scalar_t__ VIE_OP_TYPE_TWO_BYTE ; 
 int decode_two_byte_opcode (struct vie*) ; 
 TYPE_1__* one_byte_opcodes ; 
 int /*<<< orphan*/  vie_advance (struct vie*) ; 
 scalar_t__ vie_peek (struct vie*,size_t*) ; 

__attribute__((used)) static int
decode_opcode(struct vie *vie)
{
	uint8_t x;

	if (vie_peek(vie, &x))
		return (-1);

	vie->op = one_byte_opcodes[x];

	if (vie->op.op_type == VIE_OP_TYPE_NONE)
		return (-1);

	vie_advance(vie);

	if (vie->op.op_type == VIE_OP_TYPE_TWO_BYTE)
		return (decode_two_byte_opcode(vie));

	return (0);
}