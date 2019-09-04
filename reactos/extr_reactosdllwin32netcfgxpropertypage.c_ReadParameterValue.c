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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {scalar_t__ Type; size_t dwEnumOptions; size_t cchValueLength; int /*<<< orphan*/ * pszValue; TYPE_1__* pEnumOptions; } ;
struct TYPE_4__ {int /*<<< orphan*/  pszValue; } ;
typedef  TYPE_2__* PPARAMETER ;
typedef  size_t INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 size_t CB_ERR ; 
 size_t ComboBox_GetCurSel (int /*<<< orphan*/ ) ; 
 scalar_t__ ENUM_TYPE ; 
 int /*<<< orphan*/  Edit_GetText (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 size_t Edit_GetTextLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDC_PROPERTY_VALUE_EDIT ; 
 int /*<<< orphan*/  IDC_PROPERTY_VALUE_LIST ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t wcslen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
VOID
ReadParameterValue(
     HWND hwnd,
     PPARAMETER pParam)
{
    INT iIndex, iLength;

    if (pParam->Type == ENUM_TYPE)
    {
        iIndex = ComboBox_GetCurSel(GetDlgItem(hwnd, IDC_PROPERTY_VALUE_LIST));
        if (iIndex != CB_ERR && iIndex < pParam->dwEnumOptions)
        {
            iLength = wcslen(pParam->pEnumOptions[iIndex].pszValue);
            if (iLength > pParam->cchValueLength)
            {
                if (pParam->pszValue != NULL)
                    HeapFree(GetProcessHeap(), 0, pParam->pszValue);

                pParam->pszValue = HeapAlloc(GetProcessHeap(), 0, (iLength + 1) * sizeof(WCHAR));
            }

            if (pParam->pszValue != NULL)
            {
                wcscpy(pParam->pszValue,
                       pParam->pEnumOptions[iIndex].pszValue);
                pParam->cchValueLength = iLength;
            }
        }
    }
    else
    {
        iLength = Edit_GetTextLength(GetDlgItem(hwnd, IDC_PROPERTY_VALUE_EDIT));
        if (iLength > pParam->cchValueLength)
        {
            if (pParam->pszValue != NULL)
                HeapFree(GetProcessHeap(), 0, pParam->pszValue);

            pParam->pszValue = HeapAlloc(GetProcessHeap(), 0, (iLength + 1) * sizeof(WCHAR));
        }

        if (pParam->pszValue != NULL)
        {
            Edit_GetText(GetDlgItem(hwnd, IDC_PROPERTY_VALUE_EDIT),
                         pParam->pszValue,
                         iLength + 1);
            pParam->cchValueLength = iLength;
        }
    }
}