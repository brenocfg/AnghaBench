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
typedef  enum gaps_op { ____Placeholder_gaps_op } gaps_op ;

/* Variables and functions */
#define  GAPS_OP_ADD 130 
#define  GAPS_OP_SET 129 
#define  GAPS_OP_SUBTRACT 128 

__attribute__((used)) static void apply_gaps_op(int *prop, enum gaps_op op, int amount) {
	switch (op) {
	case GAPS_OP_SET:
		*prop = amount;
		break;
	case GAPS_OP_ADD:
		*prop += amount;
		break;
	case GAPS_OP_SUBTRACT:
		*prop -= amount;
		break;
	}
}