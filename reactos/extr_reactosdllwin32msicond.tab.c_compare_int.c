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
typedef  int INT ;

/* Variables and functions */
#define  COND_EQ 143 
#define  COND_GE 142 
#define  COND_GT 141 
#define  COND_IEQ 140 
#define  COND_IGE 139 
#define  COND_IGT 138 
#define  COND_ILE 137 
#define  COND_ILT 136 
#define  COND_INE 135 
#define  COND_ISS 134 
#define  COND_LE 133 
#define  COND_LHS 132 
#define  COND_LT 131 
#define  COND_NE 130 
#define  COND_RHS 129 
#define  COND_SS 128 
 int /*<<< orphan*/  ERR (char*) ; 

__attribute__((used)) static INT compare_int( INT a, INT operator, INT b )
{
    switch (operator)
    {
    case COND_LT:
    case COND_ILT:
        return a < b;
    case COND_GT:
    case COND_IGT:
        return a > b;
    case COND_EQ:
    case COND_IEQ:
        return a == b;
    case COND_NE:
    case COND_INE:
        return a != b;
    case COND_GE:
    case COND_IGE:
        return a >= b;
    case COND_LE:
    case COND_ILE:
        return a <= b;
    case COND_SS:
    case COND_ISS:
        return ( a & b ) ? 1 : 0;
    case COND_RHS:
        return ( ( a & 0xffff ) == b ) ? 1 : 0;
    case COND_LHS:
        return ( ( (a>>16) & 0xffff ) == b ) ? 1 : 0;
    default:
        ERR("invalid integer operator\n");
        return 0;
    }
    return 0;
}