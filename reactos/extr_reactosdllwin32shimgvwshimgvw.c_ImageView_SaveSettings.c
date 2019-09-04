#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_6__ {int length; int flags; TYPE_1__ rcNormalPosition; } ;
typedef  TYPE_2__ WINDOWPLACEMENT ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_7__ {int Maximized; int /*<<< orphan*/  Bottom; int /*<<< orphan*/  Right; int /*<<< orphan*/  Top; int /*<<< orphan*/  Left; } ;
typedef  int /*<<< orphan*/  SHIMGVW_SETTINGS ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetWindowPlacement (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 scalar_t__ IsZoomed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_WRITE ; 
 int /*<<< orphan*/  REG_BINARY ; 
 int /*<<< orphan*/  REG_OPTION_NON_VOLATILE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegSetValueEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int WPF_RESTORETOMAXIMIZED ; 
 int /*<<< orphan*/  _T (char*) ; 
 TYPE_3__ shiSettings ; 

__attribute__((used)) static VOID
ImageView_SaveSettings(HWND hwnd)
{
    WINDOWPLACEMENT wp;
    HKEY hKey;

    ShowWindow(hwnd, SW_HIDE);
    wp.length = sizeof(WINDOWPLACEMENT);
    GetWindowPlacement(hwnd, &wp);

    shiSettings.Left = wp.rcNormalPosition.left;
    shiSettings.Top  = wp.rcNormalPosition.top;
    shiSettings.Right  = wp.rcNormalPosition.right;
    shiSettings.Bottom = wp.rcNormalPosition.bottom;
    shiSettings.Maximized = (IsZoomed(hwnd) || (wp.flags & WPF_RESTORETOMAXIMIZED));

    if (RegCreateKeyEx(HKEY_CURRENT_USER, _T("Software\\ReactOS\\shimgvw"), 0, NULL,
        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, _T("Settings"), 0, REG_BINARY, (LPBYTE)&shiSettings, sizeof(SHIMGVW_SETTINGS));
        RegCloseKey(hKey);
    }
}