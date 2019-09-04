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
struct TYPE_4__ {int /*<<< orphan*/  lbselchstring; scalar_t__ hook; int /*<<< orphan*/  hwnd; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ LPWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ FD31_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFILEALLOC ; 
 int /*<<< orphan*/  CD_LBSELCHANGE ; 
 int /*<<< orphan*/  FD31_CallWindowProc (TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LB_ERR ; 
 int /*<<< orphan*/  LB_GETCURSEL ; 
 int /*<<< orphan*/  LB_GETTEXT ; 
 int /*<<< orphan*/  MAKELONG (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDlgItemTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  edt1 ; 
 scalar_t__ heap_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (scalar_t__) ; 
 int /*<<< orphan*/  lst1 ; 

__attribute__((used)) static LRESULT FD31_FileListSelect( const FD31_DATA *lfs )
{
    LONG lRet;
    HWND hWnd = lfs->hwnd;
    LPWSTR pstr;

    lRet =  SendDlgItemMessageW(lfs->hwnd, lst1, LB_GETCURSEL, 0, 0);
    if (lRet == LB_ERR)
        return TRUE;

    /* set the edit control to the chosen file */
    if ((pstr = heap_alloc(BUFFILEALLOC)))
    {
        SendDlgItemMessageW(hWnd, lst1, LB_GETTEXT, lRet,
                       (LPARAM)pstr);
        SetDlgItemTextW( hWnd, edt1, pstr );
        heap_free(pstr);
    }
    if (lfs->hook)
    {
        FD31_CallWindowProc(lfs, lfs->lbselchstring, lst1,
                           MAKELONG(lRet,CD_LBSELCHANGE));
    }
    /* FIXME: for OFN_ALLOWMULTISELECT we need CD_LBSELSUB, CD_SELADD,
           CD_LBSELNOITEMS */
    return TRUE;
}