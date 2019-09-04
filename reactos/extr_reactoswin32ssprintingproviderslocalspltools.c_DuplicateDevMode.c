#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ dmDriverExtra; scalar_t__ dmSize; } ;
typedef  TYPE_1__* PDEVMODEW ;

/* Variables and functions */
 int /*<<< orphan*/  CopyMemory (TYPE_1__*,TYPE_1__*,scalar_t__) ; 
 TYPE_1__* DllAllocSplMem (scalar_t__) ; 
 int /*<<< orphan*/  ERR (char*) ; 

PDEVMODEW
DuplicateDevMode(PDEVMODEW pInput)
{
    PDEVMODEW pOutput;

    // Allocate a buffer for this DevMode.
    pOutput = DllAllocSplMem(pInput->dmSize + pInput->dmDriverExtra);
    if (!pOutput)
    {
        ERR("DllAllocSplMem failed!\n");
        return NULL;
    }

    // Copy it.
    CopyMemory(pOutput, pInput, pInput->dmSize + pInput->dmDriverExtra);

    return pOutput;
}