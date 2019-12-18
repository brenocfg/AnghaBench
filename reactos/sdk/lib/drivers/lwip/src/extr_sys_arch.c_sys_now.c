#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32_t ;
struct TYPE_5__ {int QuadPart; } ;
struct TYPE_4__ {int QuadPart; } ;
typedef  TYPE_1__ LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  KeQuerySystemTime (TYPE_1__*) ; 
 TYPE_2__ StartTime ; 

u32_t sys_now(void)
{
    LARGE_INTEGER CurrentTime;
    
    KeQuerySystemTime(&CurrentTime);
    
    return (CurrentTime.QuadPart - StartTime.QuadPart) / 10000;
}