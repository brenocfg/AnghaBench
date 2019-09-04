#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_6__ {scalar_t__ lParam; } ;
struct TYPE_5__ {size_t dwCount; scalar_t__ pCurrentParam; TYPE_1__* Array; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pszName; int /*<<< orphan*/ * pszDescription; } ;
typedef  int /*<<< orphan*/ * PWSTR ;
typedef  TYPE_2__* PPARAMETER_ARRAY ;
typedef  scalar_t__ PPARAMETER ;
typedef  TYPE_3__* LPPROPSHEETPAGEW ;
typedef  scalar_t__ LPARAM ;
typedef  int /*<<< orphan*/  LONG_PTR ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ HWND ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DWLP_USER ; 
 int /*<<< orphan*/  DisplayParameter (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetDlgItem (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_PROPERTY_NAME ; 
 scalar_t__ LB_ERR ; 
 scalar_t__ ListBox_AddString (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ ListBox_GetItemData (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ListBox_SetCurSel (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ListBox_SetItemData (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SetWindowLongPtr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static
BOOL
OnInitDialog(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam)
{
    PPARAMETER_ARRAY pParamArray;
    HWND hwndControl;
    PWSTR pszText;
    DWORD i;
    INT idx;

    TRACE("OnInitDialog()\n");

    pParamArray = (PPARAMETER_ARRAY)((LPPROPSHEETPAGEW)lParam)->lParam;
    if (pParamArray == NULL)
    {
        ERR("pParamArray is NULL\n");
        return FALSE;
    }

    SetWindowLongPtr(hwnd, DWLP_USER, (LONG_PTR)pParamArray);

    hwndControl = GetDlgItem(hwnd, IDC_PROPERTY_NAME);
    if (hwndControl)
    {
        for (i = 0; i < pParamArray->dwCount; i++)
        {
            if (pParamArray->Array[i].pszDescription != NULL)
                pszText = pParamArray->Array[i].pszDescription;
            else
                pszText = pParamArray->Array[i].pszName;

            idx = ListBox_AddString(hwndControl, pszText);
            if (idx != LB_ERR)
                ListBox_SetItemData(hwndControl, idx, (LPARAM)&pParamArray->Array[i]);
        }

        if (pParamArray->dwCount > 0)
        {
            ListBox_SetCurSel(hwndControl, 0);
            pParamArray->pCurrentParam = (PPARAMETER)ListBox_GetItemData(hwndControl, 0);
            DisplayParameter(hwnd, pParamArray->pCurrentParam);
        }
    }

    return TRUE;
}