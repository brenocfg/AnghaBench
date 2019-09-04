#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; } ;
struct TYPE_11__ {scalar_t__ GreenVal; scalar_t__ BlueVal; scalar_t__ RedVal; void* hPreviewBitmap; TYPE_6__ ImageRect; TYPE_2__* Info; void* hBitmap; int /*<<< orphan*/  hPicPrev; } ;
struct TYPE_10__ {TYPE_1__* ImageEditors; } ;
struct TYPE_9__ {int /*<<< orphan*/  hBitmap; } ;
typedef  TYPE_2__* PMAIN_WND_INFO ;
typedef  TYPE_3__* PIMAGEADJUST ;
typedef  scalar_t__ LPARAM ;
typedef  TYPE_3__ IMAGEADJUST ;
typedef  int /*<<< orphan*/  HWND ;
typedef  void* HBITMAP ;

/* Variables and functions */
 scalar_t__ BASECOLOUR ; 
 int /*<<< orphan*/  BM_SETCHECK ; 
 int /*<<< orphan*/  BST_CHECKED ; 
 scalar_t__ CopyImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  IDC_BRI_EDIT ; 
 int /*<<< orphan*/  IDC_BRI_FULL ; 
 int /*<<< orphan*/  IDC_BRI_TRACKBAR ; 
 int /*<<< orphan*/  IDC_PICPREVIEW ; 
 int /*<<< orphan*/  IMAGE_BITMAP ; 
 int /*<<< orphan*/  LR_CREATEDIBSECTION ; 
 scalar_t__ MAKELONG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ProcessHeap ; 
 int /*<<< orphan*/  SendDlgItemMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SetDlgItemText (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TBM_SETPOS ; 
 int /*<<< orphan*/  TBM_SETRANGE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 

__attribute__((used)) static PIMAGEADJUST
Bri_OnInitDialog(PIMAGEADJUST pImgAdj,
             HWND hDlg,
             LPARAM lParam)
{
    pImgAdj = (IMAGEADJUST*) HeapAlloc(ProcessHeap,
                        0,
                        sizeof(IMAGEADJUST));
    if (!pImgAdj)
        return NULL;


    pImgAdj->Info = (PMAIN_WND_INFO)lParam;
    if (!pImgAdj->Info->ImageEditors)
        goto fail;


    pImgAdj->hPicPrev = GetDlgItem(hDlg, IDC_PICPREVIEW);
    GetClientRect(pImgAdj->hPicPrev,
                  &pImgAdj->ImageRect);

    /* Make a static copy of the main image */
    pImgAdj->hBitmap = (HBITMAP) CopyImage(pImgAdj->Info->ImageEditors->hBitmap,
                                 IMAGE_BITMAP,
                                 pImgAdj->ImageRect.right,
                                 pImgAdj->ImageRect.bottom,
                                 LR_CREATEDIBSECTION);
    if (!pImgAdj->hBitmap)
        goto fail;

    /* Make a copy which will be updated */
    pImgAdj->hPreviewBitmap = (HBITMAP) CopyImage(pImgAdj->Info->ImageEditors->hBitmap,
                                        IMAGE_BITMAP,
                                        pImgAdj->ImageRect.right,
                                        pImgAdj->ImageRect.bottom,
                                        LR_CREATEDIBSECTION);
    if (!pImgAdj->hPreviewBitmap)
        goto fail;


    pImgAdj->RedVal = pImgAdj->BlueVal = pImgAdj->GreenVal = 0;

    /* setup dialog */
    SendDlgItemMessage(hDlg,
                       IDC_BRI_FULL,
                       BM_SETCHECK,
                       BST_CHECKED,
                       0);
    SendDlgItemMessage(hDlg,
                       IDC_BRI_TRACKBAR,
                       TBM_SETRANGE,
                       TRUE,
                       (LPARAM)MAKELONG(0, 200));
    SendDlgItemMessage(hDlg,
                       IDC_BRI_TRACKBAR,
                       TBM_SETPOS,
                       TRUE,
                       (LPARAM)BASECOLOUR);
    SetDlgItemText(hDlg,
                   IDC_BRI_EDIT,
                   _T("100"));

    return pImgAdj;

fail:
    HeapFree(ProcessHeap,
             0,
             pImgAdj);
    return NULL;
}