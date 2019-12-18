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
typedef  scalar_t__ WORD ;
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_2__ {scalar_t__ KeybdBufferTail; scalar_t__ KeybdBufferEnd; scalar_t__ KeybdBufferStart; scalar_t__ KeybdBufferHead; } ;
typedef  scalar_t__* LPWORD ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 TYPE_1__* Bda ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN BiosKbdBufferPush(WORD Data)
{
    /* Get the location of the element after the tail */
    WORD NextElement = Bda->KeybdBufferTail + sizeof(WORD);

    /* Wrap it around if it's at or beyond the end */
    if (NextElement >= Bda->KeybdBufferEnd) NextElement = Bda->KeybdBufferStart;

    /* If it's full, fail */
    if (NextElement == Bda->KeybdBufferHead)
    {
        DPRINT1("BIOS keyboard buffer full.\n");
        return FALSE;
    }

    /* Put the value in the queue */
    *((LPWORD)((ULONG_PTR)Bda + Bda->KeybdBufferTail)) = Data;
    Bda->KeybdBufferTail = NextElement;

    /* Return success */
    return TRUE;
}