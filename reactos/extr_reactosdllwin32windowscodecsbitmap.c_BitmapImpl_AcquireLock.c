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
struct TYPE_3__ {int lock; } ;
typedef  int LONG ;
typedef  TYPE_1__ BitmapImpl ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int InterlockedCompareExchange (int*,int,int) ; 
 int TRUE ; 

__attribute__((used)) static BOOL BitmapImpl_AcquireLock(BitmapImpl *This, int write)
{
    if (write)
    {
        return 0 == InterlockedCompareExchange(&This->lock, -1, 0);
    }
    else
    {
        while (1)
        {
            LONG prev_val = This->lock;
            if (prev_val == -1)
                return FALSE;
            if (prev_val == InterlockedCompareExchange(&This->lock, prev_val+1, prev_val))
                return TRUE;
        }
    }
}