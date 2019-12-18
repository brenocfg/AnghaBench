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
typedef  int /*<<< orphan*/  LPCREATESTRUCTA ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 void* CreateWindowA (char*,char*,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ID_TEST_LABEL ; 
 scalar_t__ ID_TEST_LISTBOX ; 
 int /*<<< orphan*/  TRUE ; 
 int WS_BORDER ; 
 int WS_CHILD ; 
 int WS_TABSTOP ; 
 int WS_VISIBLE ; 
 int WS_VSCROLL ; 
 void* g_label ; 
 void* g_listBox ; 

__attribute__((used)) static BOOL on_listbox_container_create (HWND hwnd, LPCREATESTRUCTA lpcs)
{
    g_label = CreateWindowA(
        "Static",
        "Contents of static control before DlgDirList.",
        WS_CHILD | WS_VISIBLE,
        10, 10, 512, 32,
        hwnd, (HMENU)ID_TEST_LABEL, NULL, 0);
    if (!g_label) return FALSE;
    g_listBox = CreateWindowA(
        "ListBox",
        "DlgDirList test",
        WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | WS_VSCROLL,
        10, 60, 256, 256,
        hwnd, (HMENU)ID_TEST_LISTBOX, NULL, 0);
    if (!g_listBox) return FALSE;

    return TRUE;
}