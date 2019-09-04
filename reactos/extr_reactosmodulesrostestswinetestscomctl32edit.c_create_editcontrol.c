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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateWindowExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WC_EDITA ; 
 int /*<<< orphan*/  hinst ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ winetest_interactive ; 

__attribute__((used)) static HWND create_editcontrol (DWORD style, DWORD exstyle)
{
    HWND handle;

    handle = CreateWindowExA(exstyle, WC_EDITA, "Text Text", style, 10, 10, 300, 300,
        NULL, NULL, hinst, NULL);
    ok (handle != NULL, "CreateWindow EDIT Control failed\n");

    if (winetest_interactive)
	ShowWindow (handle, SW_SHOW);
    return handle;
}