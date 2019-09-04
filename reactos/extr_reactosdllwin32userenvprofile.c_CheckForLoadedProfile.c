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
struct TYPE_4__ {int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetUserSidStringFromToken (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  HKEY_USERS ; 
 int /*<<< orphan*/  MAXIMUM_ALLOWED ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlFreeUnicodeString (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static
BOOL
CheckForLoadedProfile(HANDLE hToken)
{
    UNICODE_STRING SidString;
    HKEY hKey;

    DPRINT("CheckForLoadedProfile() called\n");

    /* Get the user SID string */
    if (!GetUserSidStringFromToken(hToken, &SidString))
    {
        DPRINT1("GetUserSidStringFromToken() failed\n");
        return FALSE;
    }

    if (RegOpenKeyExW(HKEY_USERS,
                      SidString.Buffer,
                      0,
                      MAXIMUM_ALLOWED,
                      &hKey))
    {
        DPRINT("Profile not loaded\n");
        RtlFreeUnicodeString(&SidString);
        return FALSE;
    }

    RegCloseKey(hKey);

    RtlFreeUnicodeString(&SidString);

    DPRINT("Profile already loaded\n");

    return TRUE;
}