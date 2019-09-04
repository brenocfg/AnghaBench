#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {scalar_t__ lpstrFormatName; } ;
typedef  TYPE_1__ OLEUIPASTEENTRYW ;
typedef  int LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LB_ADDSTRING ; 
 int /*<<< orphan*/  LB_FINDSTRING ; 
 int /*<<< orphan*/  LB_SETITEMDATA ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL add_entry_to_lb(HWND hdlg, UINT id, OLEUIPASTEENTRYW *pe)
{
    HWND hwnd = GetDlgItem(hdlg, id);
    BOOL ret = FALSE;

    /* FIXME %s handling */

    /* Note that this suffers from the same bug as native, in that if a new string
       is a substring of an already added string, then the FINDSTRING will succeed
       this is probably not what we want */
    if(SendMessageW(hwnd, LB_FINDSTRING, 0, (LPARAM)pe->lpstrFormatName) == -1)
    {
        LRESULT pos = SendMessageW(hwnd, LB_ADDSTRING, 0, (LPARAM)pe->lpstrFormatName);
        SendMessageW(hwnd, LB_SETITEMDATA, pos, (LPARAM)pe);
        ret = TRUE;
    }
    return ret;
}