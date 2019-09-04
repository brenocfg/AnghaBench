#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct promptdisk_params {int /*<<< orphan*/  FileSought; } ;
typedef  int /*<<< orphan*/  ofn ;
typedef  scalar_t__ WCHAR ;
struct TYPE_4__ {int lStructSize; int Flags; int nMaxFile; int /*<<< orphan*/  lpstrFile; int /*<<< orphan*/  hwndOwner; } ;
typedef  TYPE_1__ OPENFILENAMEW ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 scalar_t__ GetOpenFileNameW (TYPE_1__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_PATH ; 
 int MAX_PATH ; 
 int OFN_FILEMUSTEXIST ; 
 int OFN_HIDEREADONLY ; 
 int OFN_PATHMUSTEXIST ; 
 int /*<<< orphan*/  SetDlgItemTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* strrchrW (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void promptdisk_browse(HWND hwnd, struct promptdisk_params *params)
{
    OPENFILENAMEW ofn;
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.Flags = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    ofn.hwndOwner = hwnd;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFile = HeapAlloc(GetProcessHeap(), 0, MAX_PATH*sizeof(WCHAR));
    strcpyW(ofn.lpstrFile, params->FileSought);

    if(GetOpenFileNameW(&ofn))
    {
        WCHAR* last_slash = strrchrW(ofn.lpstrFile, '\\');
        if (last_slash) *last_slash = 0;
        SetDlgItemTextW(hwnd, IDC_PATH, ofn.lpstrFile);
    }
    HeapFree(GetProcessHeap(), 0, ofn.lpstrFile);
}