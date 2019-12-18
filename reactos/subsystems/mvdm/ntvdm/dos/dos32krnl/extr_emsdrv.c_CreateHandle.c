#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t USHORT ;
struct TYPE_5__ {scalar_t__ Allocated; } ;
typedef  size_t* PUSHORT ;
typedef  TYPE_1__* PEMS_HANDLE ;

/* Variables and functions */
 size_t ARRAYSIZE (TYPE_1__*) ; 
 TYPE_1__* EmsHandleTable ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static PEMS_HANDLE CreateHandle(PUSHORT Handle)
{
    PEMS_HANDLE HandleEntry;
    USHORT i;

    /* Handle 0 is reserved (system handle) */
    for (i = 1; i < ARRAYSIZE(EmsHandleTable); i++)
    {
        HandleEntry = &EmsHandleTable[i];
        if (!HandleEntry->Allocated)
        {
            *Handle = i;
            HandleEntry->Allocated = TRUE;
            return HandleEntry;
        }
    }

    return NULL;
}