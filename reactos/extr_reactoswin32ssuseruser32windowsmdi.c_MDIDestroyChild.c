#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_6__ {scalar_t__ nActiveChildren; scalar_t__ hwndActiveChild; scalar_t__ hwndChildMaximized; scalar_t__* child; int /*<<< orphan*/  hBmpClose; } ;
typedef  TYPE_1__ MDICLIENTINFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ HWND ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 scalar_t__ GetParent (scalar_t__) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  MDI_ChildActivate (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ MDI_GetWindow (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDI_PostUpdate (scalar_t__,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  MDI_RestoreFrameMenu (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDI_SwitchActiveChild (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDI_UpdateFrameText (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SB_BOTH ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SendMessageW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_MDIREFRESHMENU ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,size_t) ; 

__attribute__((used)) static LRESULT MDIDestroyChild( HWND client, MDICLIENTINFO *ci,
                                HWND child, BOOL flagDestroy )
{
    UINT i;

    TRACE("# of managed children %u\n", ci->nActiveChildren);

    if( child == ci->hwndActiveChild )
    {
        HWND next = MDI_GetWindow(ci, child, TRUE, 0);
        if (next)
            MDI_SwitchActiveChild(ci, next, TRUE);
        else
        {
            ShowWindow(child, SW_HIDE);
            if (child == ci->hwndChildMaximized)
            {
                HWND frame = GetParent(client);
                MDI_RestoreFrameMenu(frame, child, ci->hBmpClose);
                ci->hwndChildMaximized = 0;
                MDI_UpdateFrameText(frame, client, TRUE, NULL);
            }
            if (flagDestroy)
                MDI_ChildActivate(client, 0);
        }
    }

    for (i = 0; i < ci->nActiveChildren; i++)
    {
        if (ci->child[i] == child)
        {
            HWND *new_child = HeapAlloc(GetProcessHeap(), 0, (ci->nActiveChildren - 1) * sizeof(HWND));
            if (new_child != NULL)
            {
                memcpy(new_child, ci->child, i * sizeof(HWND));
                if (i + 1 < ci->nActiveChildren)
                    memcpy(new_child + i, ci->child + i + 1, (ci->nActiveChildren - i - 1) * sizeof(HWND));
                HeapFree(GetProcessHeap(), 0, ci->child);
                ci->child = new_child;
            }
            else
            {
                UINT c;
                for (c = i; c < ci->nActiveChildren - 1; c++)
                {
                    ci->child[c] = ci->child[c+1];
                }
            }

            ci->nActiveChildren--;
            break;
        }
    }

    if (flagDestroy)
    {
        SendMessageW(client, WM_MDIREFRESHMENU, 0, 0);
        MDI_PostUpdate(GetParent(child), ci, SB_BOTH+1);
        DestroyWindow(child);
    }

    TRACE("child destroyed - %p\n", child);
    return 0;
}