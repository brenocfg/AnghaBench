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

/* Variables and functions */
 int InterlockedCompareExchange (int*,int,int) ; 

__attribute__((used)) static void BitmapImpl_ReleaseLock(BitmapImpl *This)
{
    while (1)
    {
        LONG prev_val = This->lock, new_val;
        if (prev_val == -1)
            new_val = 0;
        else
            new_val = prev_val - 1;
        if (prev_val == InterlockedCompareExchange(&This->lock, new_val, prev_val))
            break;
    }
}