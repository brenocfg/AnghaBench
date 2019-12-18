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
typedef  scalar_t__ UINT ;
struct TYPE_6__ {int mask; scalar_t__ iImage; int /*<<< orphan*/  pszText; scalar_t__ iSubItem; scalar_t__ iItem; } ;
struct TYPE_5__ {int cbSize; int /*<<< orphan*/  ImageList; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__ SP_CLASSIMAGELIST_DATA ;
typedef  int /*<<< orphan*/  (* SH_GIL_PROC ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  TYPE_2__ LV_ITEM ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/ * HMODULE ;
typedef  int /*<<< orphan*/  HIMAGELIST ;
typedef  int /*<<< orphan*/  (* FII_PROC ) (int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IDC_DEVICE ; 
 int /*<<< orphan*/  IDC_LSTVIEW ; 
 scalar_t__ IDC_SYSTEM ; 
 scalar_t__ ImageList_GetImageCount (int /*<<< orphan*/ ) ; 
 int LVIF_IMAGE ; 
 int LVIF_TEXT ; 
 int /*<<< orphan*/  LVSIL_SMALL ; 
 int /*<<< orphan*/  ListView_DeleteAllItems (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ListView_InsertItem (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ListView_SetImageList (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LoadLibrary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetupDiGetClassImageList (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _itot (scalar_t__,int /*<<< orphan*/ *,int) ; 

BOOL
DisplayImageList(HWND hwnd,
                 UINT uID)
{
    HWND hLV;
    SP_CLASSIMAGELIST_DATA ImageListData;
    LV_ITEM lvItem;
    TCHAR Buf[6];
    INT ImageListCount = -1;
    INT i = 0;

    hLV = GetDlgItem(hwnd, IDC_LSTVIEW);
    (void)ListView_DeleteAllItems(hLV);

    if (uID == IDC_SYSTEM)
    {
        HIMAGELIST hLarge, hSmall;
        HMODULE      hShell32;
        SH_GIL_PROC  Shell_GetImageLists;
        FII_PROC     FileIconInit;

        hShell32 = LoadLibrary(_T("shell32.dll"));
        if(hShell32 == NULL)
            return FALSE;

        Shell_GetImageLists = (SH_GIL_PROC)GetProcAddress(hShell32, (LPCSTR)71);
        FileIconInit = (FII_PROC)GetProcAddress(hShell32, (LPCSTR)660);

        if(Shell_GetImageLists == NULL || FileIconInit == NULL)
        {
            FreeLibrary(hShell32);
            return FALSE;
        }

        FileIconInit(TRUE);

        Shell_GetImageLists(&hLarge, &hSmall);

        ImageListCount = ImageList_GetImageCount(hSmall);

        (void)ListView_SetImageList(hLV,
                                    hSmall,
                                    LVSIL_SMALL);

        FreeLibrary(hShell32);
    }
    else if (uID == IDC_DEVICE)
    {
        ImageListData.cbSize = sizeof(SP_CLASSIMAGELIST_DATA);
        SetupDiGetClassImageList(&ImageListData);

        ImageListCount = ImageList_GetImageCount(ImageListData.ImageList);

        (void)ListView_SetImageList(hLV,
                                    ImageListData.ImageList,
                                    LVSIL_SMALL);
    }
    else
        return FALSE;

    lvItem.mask = LVIF_TEXT | LVIF_IMAGE;

    while (i <= ImageListCount)
    {
        lvItem.iItem = i;
        lvItem.iSubItem = 0;
        lvItem.pszText = _itot(i, Buf, 10);
        lvItem.iImage = i;

        (void)ListView_InsertItem(hLV, &lvItem);

        i++;
    }

    return TRUE;
}