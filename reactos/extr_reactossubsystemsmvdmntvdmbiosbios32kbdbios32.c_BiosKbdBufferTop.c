#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_2__ {scalar_t__ KeybdBufferHead; scalar_t__ KeybdBufferTail; } ;
typedef  int /*<<< orphan*/ * LPWORD ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 TYPE_1__* Bda ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN BiosKbdBufferTop(LPWORD Data)
{
    /* If it's empty, fail */
    if (Bda->KeybdBufferHead == Bda->KeybdBufferTail) return FALSE;

    /* Otherwise, get the value and return success */
    *Data = *((LPWORD)((ULONG_PTR)Bda + Bda->KeybdBufferHead));

    return TRUE;
}