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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  REGSAM ;
typedef  scalar_t__ MSIINSTALLCONTEXT ;
typedef  char* LPSTR ;
typedef  char* LPCSTR ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  KEY_WOW64_64KEY ; 
 int MAX_PATH ; 
 scalar_t__ MSIINSTALLCONTEXT_MACHINE ; 
 scalar_t__ MSIINSTALLCONTEXT_USERMANAGED ; 
 scalar_t__ MSIINSTALLCONTEXT_USERUNMANAGED ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ is_wow64 ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  package_RegDeleteTreeW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 int /*<<< orphan*/  squash_guid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void delete_component_path(LPCSTR guid, MSIINSTALLCONTEXT context, LPSTR usersid)
{
    WCHAR guidW[MAX_PATH];
    WCHAR squashedW[MAX_PATH];
    WCHAR substrW[MAX_PATH];
    CHAR squashed[MAX_PATH];
    CHAR comppath[MAX_PATH];
    CHAR prodpath[MAX_PATH];
    REGSAM access = KEY_ALL_ACCESS;

    if (is_wow64)
        access |= KEY_WOW64_64KEY;

    MultiByteToWideChar(CP_ACP, 0, guid, -1, guidW, MAX_PATH);
    squash_guid(guidW, squashedW);
    WideCharToMultiByte(CP_ACP, 0, squashedW, -1, squashed, MAX_PATH, NULL, NULL);

    if (context == MSIINSTALLCONTEXT_MACHINE)
    {
        sprintf(comppath,
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\"
                "Installer\\UserData\\S-1-5-18\\Components\\%s", squashed);
        lstrcpyA(prodpath,
                 "SOFTWARE\\Classes\\Installer\\"
                 "Products\\3D0DAE300FACA1300AD792060BCDAA92");
    }
    else if (context == MSIINSTALLCONTEXT_USERUNMANAGED)
    {
        sprintf(comppath,
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\"
                "Installer\\UserData\\%s\\Components\\%s", usersid, squashed);
        sprintf(prodpath,
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\"
                "Installer\\%s\\Installer\\Products\\"
                "7D2F387510109040002000060BECB6AB", usersid);
    }
    else if (context == MSIINSTALLCONTEXT_USERMANAGED)
    {
        sprintf(comppath,
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\"
                "Installer\\UserData\\%s\\Components\\%s", usersid, squashed);
        sprintf(prodpath,
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\"
                "Installer\\Managed\\%s\\Installer\\Products\\"
                "7D2F387510109040002000060BECB6AB", usersid);
    }

    MultiByteToWideChar(CP_ACP, 0, comppath, -1, substrW, MAX_PATH);
    package_RegDeleteTreeW(HKEY_LOCAL_MACHINE, substrW, access);

    MultiByteToWideChar(CP_ACP, 0, prodpath, -1, substrW, MAX_PATH);
    package_RegDeleteTreeW(HKEY_LOCAL_MACHINE, substrW, access);
}