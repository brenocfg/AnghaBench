#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  browse_info ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BrsFolder_OnSetSelectionW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static BOOL BrsFolder_OnSetSelectionA(browse_info *info, LPVOID selection, BOOL is_str) {
    LPWSTR selectionW = NULL;
    BOOL result = FALSE;
    int length;
    
    if (!is_str)
        return BrsFolder_OnSetSelectionW(info, selection, is_str);

    if ((length = MultiByteToWideChar(CP_ACP, 0, selection, -1, NULL, 0)) &&
        (selectionW = HeapAlloc(GetProcessHeap(), 0, length * sizeof(WCHAR))) &&
        MultiByteToWideChar(CP_ACP, 0, selection, -1, selectionW, length))
    {
        result = BrsFolder_OnSetSelectionW(info, selectionW, is_str);
    }

    HeapFree(GetProcessHeap(), 0, selectionW);
    return result;
}