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
typedef  int UINT ;
struct TYPE_3__ {int /*<<< orphan*/  hWnd; int /*<<< orphan*/  hWndListView; } ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  TYPE_1__ CPanel ;

/* Variables and functions */
 int /*<<< orphan*/  CheckMenuRadioItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FCIDM_SHVIEW_BIGICON ; 
 int /*<<< orphan*/  FCIDM_SHVIEW_REPORTVIEW ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetMenu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSubMenu (int /*<<< orphan*/ ,int) ; 
 int LISTVIEW_DEFSTYLE ; 
 int /*<<< orphan*/  MF_BYCOMMAND ; 
 int /*<<< orphan*/  SetWindowLongW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void Control_UpdateListViewStyle(CPanel *panel, UINT style, UINT id)
{
    HMENU hMenu, hSubMenu;

    SetWindowLongW(panel->hWndListView, GWL_STYLE, LISTVIEW_DEFSTYLE | style);

    /* update the menu */
    hMenu = GetMenu(panel->hWnd);
    hSubMenu = GetSubMenu(hMenu, 1);

    CheckMenuRadioItem(hSubMenu, FCIDM_SHVIEW_BIGICON, FCIDM_SHVIEW_REPORTVIEW,
        id, MF_BYCOMMAND);
}