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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int UCHAR ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int FALSE ; 
#define  VER_EQUAL 132 
#define  VER_GREATER 131 
#define  VER_GREATER_EQUAL 130 
#define  VER_LESS 129 
#define  VER_LESS_EQUAL 128 

__attribute__((used)) static BOOLEAN
RtlpVerCompare(ULONG left, ULONG right, UCHAR Condition)
{
    switch (Condition)
    {
        case VER_EQUAL:
            return (left == right);
        case VER_GREATER:
            return (left > right);
        case VER_GREATER_EQUAL:
            return (left >= right);
        case VER_LESS:
            return (left < right);
        case VER_LESS_EQUAL:
            return (left <= right);
        default:
            break;
    }
    return FALSE;
}