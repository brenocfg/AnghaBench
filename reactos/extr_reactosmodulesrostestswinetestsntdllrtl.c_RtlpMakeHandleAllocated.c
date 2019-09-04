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
typedef  int ULONG_PTR ;
struct TYPE_3__ {int /*<<< orphan*/  Next; } ;
typedef  TYPE_1__ RTL_HANDLE ;

/* Variables and functions */

__attribute__((used)) static inline void RtlpMakeHandleAllocated(RTL_HANDLE * Handle)
{
    ULONG_PTR *AllocatedBit = (ULONG_PTR *)(&Handle->Next);
    *AllocatedBit = *AllocatedBit | 1;
}