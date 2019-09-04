#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int cLockObj; int /*<<< orphan*/  h; } ;
struct TYPE_6__ {TYPE_1__ head; int /*<<< orphan*/  spkf; struct TYPE_6__* pklPrev; struct TYPE_6__* pklNext; int /*<<< orphan*/  dwKL_Flags; } ;
typedef  TYPE_2__* PKL ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KLF_UNLOAD ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TYPE_KBDLAYOUT ; 
 int /*<<< orphan*/  UnloadKbdFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UserDeleteObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* gspklBaseLayout ; 

BOOL
UserUnloadKbl(PKL pKl)
{
    /* According to msdn, UnloadKeyboardLayout can fail
       if the keyboard layout identifier was preloaded. */
    if (pKl == gspklBaseLayout)
    {
        if (pKl->pklNext == pKl->pklPrev)
        {
            /* There is only one layout */
            return FALSE;
        }

        /* Set next layout as default */
        gspklBaseLayout = pKl->pklNext;
    }

    if (pKl->head.cLockObj > 1)
    {
        /* Layout is used by other threads */
        pKl->dwKL_Flags |= KLF_UNLOAD;
        return FALSE;
    }

    /* Unload the layout */
    pKl->pklPrev->pklNext = pKl->pklNext;
    pKl->pklNext->pklPrev = pKl->pklPrev;
    UnloadKbdFile(pKl->spkf);
    UserDeleteObject(pKl->head.h, TYPE_KBDLAYOUT);
    return TRUE;
}