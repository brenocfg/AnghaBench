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
typedef  int OrderOperator ;

/* Variables and functions */
#define  ORDER_EQUAL 133 
#define  ORDER_GREATER 132 
#define  ORDER_GREATER_OR_EQUAL 131 
#define  ORDER_LOWER 130 
#define  ORDER_LOWER_OR_EQUAL 129 
#define  ORDER_UNEQUAL 128 
 int /*<<< orphan*/  assert_not_reached (char*) ; 

__attribute__((used)) static bool test_order(int k, OrderOperator p) {

        switch (p) {

        case ORDER_LOWER:
                return k < 0;

        case ORDER_LOWER_OR_EQUAL:
                return k <= 0;

        case ORDER_EQUAL:
                return k == 0;

        case ORDER_UNEQUAL:
                return k != 0;

        case ORDER_GREATER_OR_EQUAL:
                return k >= 0;

        case ORDER_GREATER:
                return k > 0;

        default:
                assert_not_reached("unknown order");

        }
}