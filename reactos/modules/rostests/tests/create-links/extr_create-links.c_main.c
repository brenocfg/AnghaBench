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
typedef  int /*<<< orphan*/  LPSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CSIDL_DESKTOP ; 
 int /*<<< orphan*/  CSIDL_PROGRAMS ; 
 int /*<<< orphan*/  CoInitialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 int /*<<< orphan*/  CreateShellLink (char*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  PathAddBackslash (char*) ; 
 int /*<<< orphan*/  SHGetSpecialFolderPathA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int main()
{
	char path[MAX_PATH];
	LPSTR p;

	CoInitialize(NULL);

	/* create some shortcuts in the start menu "programs" folder */
	SHGetSpecialFolderPathA(0, path, CSIDL_PROGRAMS, TRUE);
	p = PathAddBackslash(path);

	strcpy(p, "start-cmd.lnk");
	CreateShellLink(path, "cmd.exe", "", NULL, NULL, 0, "open console window");

	strcpy(p, "start-winhello.lnk");
	CreateShellLink(path, "winhello.exe", "", NULL, NULL, 0, "launch winhello");


	/* create some shortcuts on the desktop */
	SHGetSpecialFolderPathA(0, path, CSIDL_DESKTOP, TRUE);
	p = PathAddBackslash(path);

	strcpy(p, "start-wcmd.lnk");
	CreateShellLink(path, "cmd.exe", "", NULL, NULL, 0, "open console window");

	strcpy(p, "start-winemine.lnk");
	CreateShellLink(path, "winemine.exe", "", NULL, NULL, 0, "launch winemine");

	CoUninitialize();

	return 0;
}