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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int dwMajorVersion; int dwMinorVersion; int wSuiteMask; scalar_t__ wProductType; int /*<<< orphan*/  szCSDVersion; scalar_t__ dwBuildNumber; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__* LPOSVERSIONINFOEX ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetComputerName (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ VER_NT_DOMAIN_CONTROLLER ; 
 scalar_t__ VER_NT_SERVER ; 
 scalar_t__ VER_NT_WORKSTATION ; 
 int VER_SUITE_BLADE ; 
 int VER_SUITE_DATACENTER ; 
 int VER_SUITE_EMBEDDEDNT ; 
 int VER_SUITE_ENTERPRISE ; 
 int VER_SUITE_PERSONAL ; 
 int VER_SUITE_SMALLBUSINESS ; 
 int VER_SUITE_SMALLBUSINESS_RESTRICTED ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _stprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _tcscat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _tcscpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

VOID
GetBasicInfo(LPOSVERSIONINFOEX osvi, TCHAR * HostName, TCHAR * OSName, TCHAR * Version, TCHAR * Role, TCHAR * Components)
{
	/* Host Name - COMPUTERNAME*/
	DWORD  bufCharCount = 1024;
	GetComputerName(HostName, &bufCharCount);


	/* OSName - Windows XP Home Editition */
	if(osvi->dwMajorVersion == 4)
	{
		_tcscpy(OSName, _T("Microsoft Windows NT 4.0 "));
	}
	else if(osvi->dwMajorVersion == 5)
	{
		if(osvi->dwMinorVersion == 0)
		{
			_tcscpy(OSName, _T("Microsoft Windows 2000 "));
		}
		else if(osvi->dwMinorVersion == 1)
		{
			_tcscpy(OSName, _T("Microsoft Windows XP "));
		}
		else if(osvi->dwMinorVersion == 2)
		{
			_tcscpy(OSName, _T("Microsoft Windows Server 2003 "));
		}
	}
	else if(osvi->dwMajorVersion == 6)
	{
		_tcscpy(OSName, _T("Microsoft Windows Vista "));
	}
	else
	{
		_tcscpy(OSName, _T("Microsoft Windows "));
	}

	if(osvi->wSuiteMask & VER_SUITE_BLADE)
		_tcscat(OSName, _T("Web Edition"));
	if(osvi->wSuiteMask & VER_SUITE_DATACENTER)
		_tcscat(OSName, _T("Datacenter"));
	if(osvi->wSuiteMask & VER_SUITE_ENTERPRISE)
		_tcscat(OSName, _T("Enterprise"));
	if(osvi->wSuiteMask & VER_SUITE_EMBEDDEDNT)
		_tcscat(OSName, _T("Embedded"));
	if(osvi->wSuiteMask & VER_SUITE_PERSONAL)
		_tcscat(OSName, _T("Home Edition"));
	if(osvi->wSuiteMask & VER_SUITE_SMALLBUSINESS_RESTRICTED && osvi->wSuiteMask & VER_SUITE_SMALLBUSINESS)
		_tcscat(OSName, _T("Small Bussiness Edition"));

	/* Version - 5.1 Build 2600 Serivce Pack 2 */
	_stprintf(Version, _T("%d.%d Build %d %s"),(int)osvi->dwMajorVersion,(int)osvi->dwMinorVersion,(int)osvi->dwBuildNumber, osvi->szCSDVersion);

	/* Role - Workgroup / Server / Domain Controller */
	if(osvi->wProductType == VER_NT_DOMAIN_CONTROLLER)
		_tcscpy(Role, _T("Domain Controller"));
	else if(osvi->wProductType == VER_NT_SERVER)
		_tcscpy(Role, _T("Server"));
	else if(osvi->wProductType == VER_NT_WORKSTATION)
		_tcscpy(Role, _T("Workgroup"));

	/* Components - FIXME: what is something that might be installed? */
	_tcscat(Components, _T("Not Installed"));

}