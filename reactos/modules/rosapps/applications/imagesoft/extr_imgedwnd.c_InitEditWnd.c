#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int Zoom; int /*<<< orphan*/  hSelf; TYPE_2__* MainWnd; struct TYPE_10__* Next; TYPE_1__* OpenInfo; int /*<<< orphan*/ * hDCMem; } ;
struct TYPE_9__ {TYPE_3__* ImageEditors; } ;
struct TYPE_8__ {scalar_t__ CreateNew; } ;
typedef  TYPE_3__* PEDIT_WND_INFO ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EditWndUpdateScrollInfo (TYPE_3__*) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadBlankCanvas (TYPE_3__*) ; 
 int /*<<< orphan*/  LoadDIBImage (TYPE_3__*) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL
InitEditWnd(PEDIT_WND_INFO Info)
{
    //BOOL bRet = FALSE;

    Info->Zoom = 100;

    if (Info->OpenInfo != NULL)
    {
        HDC hDC;

        if (Info->hDCMem)
        {
            DeleteObject(Info->hDCMem);
            Info->hDCMem = NULL;
        }

        hDC = GetDC(Info->hSelf);
        Info->hDCMem = CreateCompatibleDC(hDC);
        ReleaseDC(Info->hSelf, hDC);

        if (Info->OpenInfo->CreateNew)
        {
            LoadBlankCanvas(Info);
        }
        else
        {
            LoadDIBImage(Info);
        }

        Info->OpenInfo = NULL;
    }

    EditWndUpdateScrollInfo(Info);

    /* Add image editor to the list */
    Info->Next = Info->MainWnd->ImageEditors;
    Info->MainWnd->ImageEditors = Info;

    InvalidateRect(Info->hSelf,
                   NULL,
                   TRUE);

    /* FIXME - if returning FALSE, remove the image editor from the list! */
    return TRUE;
}