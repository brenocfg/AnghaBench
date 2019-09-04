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
typedef  int /*<<< orphan*/ * HWND ;
typedef  int BOOL ;

/* Variables and functions */
 int CloseClipboard () ; 
 int /*<<< orphan*/ * CreateWindowW (char*,char*,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int EmptyClipboard () ; 
 int /*<<< orphan*/ * GetClipboardOwner () ; 
 int OpenClipboard (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WS_OVERLAPPEDWINDOW ; 
 int /*<<< orphan*/  ok (int,char*) ; 

void TestOwnership()
{
    BOOL ret;
    HWND hWnd, hWndClipOwner;

    ret = OpenClipboard(NULL);
    ok (ret, "OpenClipboard failed\n");

    ret = EmptyClipboard();
    ok (ret, "EmptyClipboard failed\n");

    ret = CloseClipboard();
    ok (ret, "CloseClipboard failed\n");

    hWndClipOwner = GetClipboardOwner();
    ok (hWndClipOwner == NULL, "Expected NULL owner\n");

    hWnd = CreateWindowW(L"static", L"static", WS_OVERLAPPEDWINDOW, 20, 20, 300, 300, NULL, NULL, 0, NULL);
    ok (hWnd != 0 , "CreateWindowW failed\n");

    ret = OpenClipboard(hWnd);
    ok (ret, "OpenClipboard failed\n");

    hWndClipOwner = GetClipboardOwner();
    ok (hWndClipOwner == NULL, "Expected NULL owner\n");

    ret = EmptyClipboard();
    ok (ret, "EmptyClipboard failed\n");

    ret = CloseClipboard();
    ok (ret, "CloseClipboard failed\n");

    hWndClipOwner = GetClipboardOwner();
    ok (hWndClipOwner == hWnd, "Expected hWnd owner\n");

    DestroyWindow(hWnd);
}