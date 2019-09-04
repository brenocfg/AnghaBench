#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* WORD ;
struct TYPE_4__ {void* InvMod; void* InvComb; } ;
typedef  TYPE_1__ HOTKEY_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,void*,void*) ; 

__attribute__((used)) static void 
HOTKEY_SetRules(HOTKEY_INFO *infoPtr, WORD invComb, WORD invMod)
{
    infoPtr->InvComb = invComb;
    infoPtr->InvMod = invMod;
    TRACE("(infoPtr=%p) Invalid Modifers: 0x%x, If Invalid: 0x%x\n", infoPtr,
          infoPtr->InvComb, infoPtr->InvMod);
}