#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_13__ {int Flags; int lStructSize; scalar_t__ lpfnHook; } ;
struct TYPE_12__ {int Flags; int lStructSize; scalar_t__ lpfnHook; } ;
struct TYPE_11__ {int open; void* fileokstring; void* lbselchstring; TYPE_2__* ofnW; TYPE_3__* ofnA; void* hook; scalar_t__ lParam; } ;
typedef  TYPE_1__* PFD31_DATA ;
typedef  TYPE_2__* LPOPENFILENAMEW ;
typedef  TYPE_3__* LPOPENFILENAMEA ;
typedef  scalar_t__ LPARAM ;
typedef  TYPE_1__ FD31_DATA ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  FD31_DestroyPrivate (TYPE_1__*) ; 
 int /*<<< orphan*/  FD31_GetTemplate (TYPE_1__*) ; 
 int /*<<< orphan*/  FD31_MapOfnStructA (TYPE_3__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  FILEOKSTRINGA ; 
 int /*<<< orphan*/  LBSELCHSTRINGA ; 
 int OFN_ENABLEHOOK ; 
 scalar_t__ OPEN_DIALOG ; 
 void* RegisterWindowMessageA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 void* TRUE ; 
 void* heap_alloc_zero (int) ; 

__attribute__((used)) static PFD31_DATA FD31_AllocPrivate(LPARAM lParam, UINT dlgType, BOOL IsUnicode)
{
    FD31_DATA *lfs = heap_alloc_zero(sizeof(*lfs));

    TRACE("alloc private buf %p\n", lfs);
    if (!lfs) return NULL;
    lfs->hook = FALSE;
    lfs->lParam = lParam;
    lfs->open = (dlgType == OPEN_DIALOG);

    if (IsUnicode)
    {
        lfs->ofnA = NULL;
        lfs->ofnW = (LPOPENFILENAMEW) lParam;
        if (lfs->ofnW->Flags & OFN_ENABLEHOOK)
            if (lfs->ofnW->lpfnHook)
                lfs->hook = TRUE;
    }
    else
    {
        lfs->ofnA = (LPOPENFILENAMEA) lParam;
        if (lfs->ofnA->Flags & OFN_ENABLEHOOK)
            if (lfs->ofnA->lpfnHook)
                lfs->hook = TRUE;
        lfs->ofnW = heap_alloc_zero(lfs->ofnA->lStructSize);
        lfs->ofnW->lStructSize = lfs->ofnA->lStructSize;
        FD31_MapOfnStructA(lfs->ofnA, lfs->ofnW, lfs->open);
    }

    if (! FD31_GetTemplate(lfs))
    {
        FD31_DestroyPrivate(lfs);
        return NULL;
    }
    lfs->lbselchstring = RegisterWindowMessageA(LBSELCHSTRINGA);
    lfs->fileokstring = RegisterWindowMessageA(FILEOKSTRINGA);

    return lfs;
}