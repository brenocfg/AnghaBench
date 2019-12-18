#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {struct TYPE_5__* Next; TYPE_1__* MainWnd; int /*<<< orphan*/  pBits; int /*<<< orphan*/  pbmi; int /*<<< orphan*/  hDCMem; } ;
struct TYPE_4__ {TYPE_2__* ImageEditors; } ;
typedef  TYPE_2__* PEDIT_WND_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcessHeap ; 

__attribute__((used)) static VOID
DestroyEditWnd(PEDIT_WND_INFO Info)
{
    PEDIT_WND_INFO *PrevEditor;
    PEDIT_WND_INFO Editor;

    DeleteDC(Info->hDCMem);

    /* FIXME - free resources and run down editor */
    HeapFree(ProcessHeap,
             0,
             Info->pbmi);
    HeapFree(ProcessHeap,
             0,
             Info->pBits);

    /* Remove the image editor from the list */
    PrevEditor = &Info->MainWnd->ImageEditors;
    Editor = Info->MainWnd->ImageEditors;
    do
    {
        if (Editor == Info)
        {
            *PrevEditor = Info->Next;
            break;
        }
        PrevEditor = &Editor->Next;
        Editor = Editor->Next;
    } while (Editor != NULL);
}