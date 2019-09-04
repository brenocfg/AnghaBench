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
typedef  scalar_t__ UINT ;

/* Variables and functions */
 scalar_t__ DRIVE_REMOTE ; 
 int FALSE ; 
 scalar_t__ GetDriveTypeA (char*) ; 
 scalar_t__ WINVER_WIN8 ; 
 scalar_t__ g_WinVersion ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pAllowPermLayer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char) ; 
 int wrapAllowPermLayer (char*) ; 

__attribute__((used)) static void test_AllowPermLayer(void)
{
    char buf[20];
    char drive_letter;
    UINT drivetype = 0;
    ok(pAllowPermLayer(NULL) == FALSE, "Expected AllowPermLayer to fail for NULL\n");
    if (g_WinVersion < WINVER_WIN8)
    {
        ok(wrapAllowPermLayer("-:"), "Expected AllowPermLayer to succeed\n");
        ok(wrapAllowPermLayer("@:"), "Expected AllowPermLayer to succeed\n");
        ok(wrapAllowPermLayer("4:"), "Expected AllowPermLayer to succeed\n");
        ok(wrapAllowPermLayer("*:"), "Expected AllowPermLayer to succeed\n");
    }
    ok(wrapAllowPermLayer("*a") == FALSE, "Expected AllowPermLayer to fail\n");
    ok(wrapAllowPermLayer("*\\") == FALSE, "Expected AllowPermLayer to fail\n");
    for (drive_letter = 'a'; drive_letter <= 'z'; ++drive_letter)
    {
        sprintf(buf, "%c:\\", drive_letter);
        drivetype = GetDriveTypeA(buf);
        ok(wrapAllowPermLayer(buf) == (drivetype != DRIVE_REMOTE), "Expected AllowPermLayer to be %d for %c:\\\n", (drivetype != DRIVE_REMOTE), drive_letter);
    }
}