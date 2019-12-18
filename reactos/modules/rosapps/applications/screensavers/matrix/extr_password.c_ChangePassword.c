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
typedef  int /*<<< orphan*/  (* PWDCHANGEPASSWORD ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/ * HINSTANCE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * LoadLibrary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 

BOOL ChangePassword(HWND hwnd)
{
	// This only ever gets called under '95, when started with the /a option.
	HINSTANCE hmpr = LoadLibrary(_T("MPR.DLL"));
	PWDCHANGEPASSWORD PwdChangePassword;

	if(hmpr == NULL)
		return FALSE;

	PwdChangePassword = (PWDCHANGEPASSWORD)GetProcAddress(hmpr, "PwdChangePasswordA");

	if(PwdChangePassword == NULL)
	{
		FreeLibrary(hmpr);
		return FALSE;
	}

	PwdChangePassword(_T("SCRSAVE"), hwnd, 0, 0);
	FreeLibrary(hmpr);

	return TRUE;
}