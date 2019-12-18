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
struct TYPE_3__ {scalar_t__ uiNumStars; scalar_t__ uiSpeed; scalar_t__ uiRotation; scalar_t__ bDoBlending; scalar_t__ bFinePerspective; scalar_t__ bEnableFiltering; scalar_t__ bSmoothShading; } ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 TYPE_1__ FactoryDefaults ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  KEY_READ ; 
 scalar_t__ MAX_SPEED ; 
 scalar_t__ MAX_STARS ; 
 scalar_t__ MIN_SPEED ; 
 scalar_t__ MIN_STARS ; 
 void* QueryDWORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ROTATION_LINEAR ; 
 scalar_t__ ROTATION_NONE ; 
 scalar_t__ ROTATION_PERIODIC ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ Settings ; 
 int /*<<< orphan*/  _T (char*) ; 

void LoadSettings(void)
{
    HKEY  hKey;
    LONG  lRes;

    Settings = FactoryDefaults;

    lRes = RegCreateKeyEx(
            HKEY_CURRENT_USER,
            _T("Software\\Microsoft\\ScreenSavers\\Ssstars"),
            0,
            _T(""),
            0,
            KEY_READ,
            NULL,
            &hKey,
            NULL);

    if (lRes != ERROR_SUCCESS)
        return;

    Settings.uiNumStars = QueryDWORD(hKey, _T("NumberOfStars"),  Settings.uiNumStars);
    Settings.uiSpeed    = QueryDWORD(hKey, _T("Speed"),          Settings.uiSpeed);
    Settings.uiRotation = QueryDWORD(hKey, _T("TypeOfRotation"), Settings.uiRotation);

    Settings.bDoBlending      = QueryDWORD(hKey, _T("DoBlending"),      Settings.bDoBlending);
    Settings.bFinePerspective = QueryDWORD(hKey, _T("FinePerspective"), Settings.bFinePerspective);
    Settings.bEnableFiltering = QueryDWORD(hKey, _T("EnableFiltering"), Settings.bEnableFiltering);
    Settings.bSmoothShading   = QueryDWORD(hKey, _T("SmoothShading"),   Settings.bSmoothShading);

    // Check the number of stars to be in range
    if (Settings.uiNumStars < MIN_STARS)
        Settings.uiNumStars = MIN_STARS;
    else
    if (Settings.uiNumStars > MAX_STARS)
        Settings.uiNumStars = MAX_STARS;

    // Check the speed to be in range
    if (Settings.uiSpeed < MIN_SPEED)
        Settings.uiSpeed = MIN_SPEED;
    else
    if (Settings.uiSpeed > MAX_SPEED)
        Settings.uiSpeed = MAX_SPEED;

    // Check type of rotation to be in range
    if (Settings.uiRotation != ROTATION_NONE &&
        Settings.uiRotation != ROTATION_LINEAR &&
        Settings.uiRotation != ROTATION_PERIODIC)
        Settings.uiRotation = ROTATION_PERIODIC;

    RegCloseKey(hKey);
}