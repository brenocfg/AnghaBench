#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  bSmoothShading; int /*<<< orphan*/  bEnableFiltering; int /*<<< orphan*/  bFinePerspective; int /*<<< orphan*/  bDoBlending; int /*<<< orphan*/  uiRotation; int /*<<< orphan*/  uiSpeed; int /*<<< orphan*/  uiNumStars; } ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  KEY_WRITE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SaveDWORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ Settings ; 
 int /*<<< orphan*/  _T (char*) ; 

void SaveSettings(void)
{
    HKEY  hKey;
    LONG  lRes;

    lRes = RegCreateKeyEx(
            HKEY_CURRENT_USER,
            _T("Software\\Microsoft\\ScreenSavers\\Ssstars"),
            0,
            _T(""),
            0,
            KEY_WRITE,
            NULL,
            &hKey,
            NULL);

    if (lRes != ERROR_SUCCESS)
        return;

    SaveDWORD(hKey, _T("NumberOfStars"),  Settings.uiNumStars);
    SaveDWORD(hKey, _T("Speed"),          Settings.uiSpeed);
    SaveDWORD(hKey, _T("TypeOfRotation"), Settings.uiRotation);

    SaveDWORD(hKey, _T("DoBlending"),      Settings.bDoBlending);
    SaveDWORD(hKey, _T("FinePerspective"), Settings.bFinePerspective);
    SaveDWORD(hKey, _T("EnableFiltering"), Settings.bEnableFiltering);
    SaveDWORD(hKey, _T("SmoothShading"),   Settings.bSmoothShading);

    RegCloseKey(hKey);
}