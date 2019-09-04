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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_2__ {scalar_t__ wProcessorArchitecture; } ;
typedef  int /*<<< orphan*/  SYSTEM_INFO ;
typedef  int /*<<< orphan*/  REGSAM ;
typedef  char MSIHANDLE ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int LANGID ;
typedef  int INSTALLUILEVEL ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CSIDL_PROGRAM_FILES ; 
 int /*<<< orphan*/  CSIDL_PROGRAM_FILESX86 ; 
 int /*<<< orphan*/  CSIDL_PROGRAM_FILES_COMMON ; 
 int /*<<< orphan*/  CSIDL_PROGRAM_FILES_COMMONX86 ; 
 int /*<<< orphan*/  CURR_DIR ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/  ERROR_INSTALL_PACKAGE_REJECTED ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetSystemDirectoryA (char*,int) ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int GetUserDefaultLangID () ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int INSTALLUILEVEL_BASIC ; 
 int INSTALLUILEVEL_NONE ; 
 int INSTALLUILEVEL_SOURCERESONLY ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  KEY_WOW64_64KEY ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MsiCloseHandle (char) ; 
 int /*<<< orphan*/  MsiGetPropertyA (char,char*,char*,int*) ; 
 int MsiSetInternalUI (int,int /*<<< orphan*/ *) ; 
 scalar_t__ PROCESSOR_ARCHITECTURE_AMD64 ; 
 scalar_t__ PROCESSOR_ARCHITECTURE_INTEL ; 
 int REG_SZ ; 
 int /*<<< orphan*/  RegOpenKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegOpenKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int*) ; 
 TYPE_1__ S (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_CXSCREEN ; 
 int /*<<< orphan*/  SM_CYSCREEN ; 
 int /*<<< orphan*/  U (int /*<<< orphan*/ ) ; 
 int atol (char*) ; 
 char create_package_db () ; 
 int /*<<< orphan*/  is_root (int /*<<< orphan*/ ) ; 
 scalar_t__ is_wow64 ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  lstrcmpiA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,int /*<<< orphan*/ ) ; 
 char* msifile ; 
 int /*<<< orphan*/  ok (char,char*,...) ; 
 int /*<<< orphan*/  pGetSystemInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pGetSystemWow64DirectoryA (char*,int) ; 
 int /*<<< orphan*/  pSHGetFolderPathA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  package_from_db (char,char*) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static void test_installprops(void)
{
    MSIHANDLE hpkg, hdb;
    CHAR path[MAX_PATH], buf[MAX_PATH];
    DWORD size, type;
    LANGID langid;
    HKEY hkey1, hkey2;
    int res;
    UINT r;
    REGSAM access = KEY_ALL_ACCESS;
    SYSTEM_INFO si;
    INSTALLUILEVEL uilevel;

    if (is_wow64)
        access |= KEY_WOW64_64KEY;

    lstrcpyA(path, CURR_DIR);
    if (!is_root(CURR_DIR)) lstrcatA(path, "\\");
    lstrcatA(path, msifile);

    uilevel = MsiSetInternalUI(INSTALLUILEVEL_BASIC|INSTALLUILEVEL_SOURCERESONLY, NULL);

    hdb = create_package_db();
    ok( hdb, "failed to create database\n");

    r = package_from_db(hdb, &hpkg);
    if (r == ERROR_INSTALL_PACKAGE_REJECTED)
    {
        skip("Not enough rights to perform tests\n");
        MsiSetInternalUI(uilevel, NULL);
        DeleteFileA(msifile);
        return;
    }
    ok( r == ERROR_SUCCESS, "failed to create package %u\n", r );

    MsiCloseHandle(hdb);

    buf[0] = 0;
    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "UILevel", buf, &size);
    ok( r == ERROR_SUCCESS, "failed to get property: %d\n", r);
    ok( !lstrcmpA(buf, "3"), "Expected \"3\", got \"%s\"\n", buf);

    MsiSetInternalUI(INSTALLUILEVEL_NONE, NULL);

    buf[0] = 0;
    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "UILevel", buf, &size);
    ok( r == ERROR_SUCCESS, "failed to get property: %d\n", r);
    ok( !lstrcmpA(buf, "3"), "Expected \"3\", got \"%s\"\n", buf);

    buf[0] = 0;
    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "DATABASE", buf, &size);
    ok( r == ERROR_SUCCESS, "failed to get property: %d\n", r);
    ok( !lstrcmpA(buf, path), "Expected %s, got %s\n", path, buf);

    RegOpenKeyA(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\MS Setup (ACME)\\User Info", &hkey1);
    RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, access, &hkey2);

    size = MAX_PATH;
    type = REG_SZ;
    *path = '\0';
    if (RegQueryValueExA(hkey1, "DefName", NULL, &type, (LPBYTE)path, &size) != ERROR_SUCCESS)
    {
        size = MAX_PATH;
        type = REG_SZ;
        RegQueryValueExA(hkey2, "RegisteredOwner", NULL, &type, (LPBYTE)path, &size);
    }

    buf[0] = 0;
    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "USERNAME", buf, &size);
    ok( r == ERROR_SUCCESS, "failed to get property: %d\n", r);
    ok( !lstrcmpA(buf, path), "Expected %s, got %s\n", path, buf);

    size = MAX_PATH;
    type = REG_SZ;
    *path = '\0';
    if (RegQueryValueExA(hkey1, "DefCompany", NULL, &type, (LPBYTE)path, &size) != ERROR_SUCCESS)
    {
        size = MAX_PATH;
        type = REG_SZ;
        RegQueryValueExA(hkey2, "RegisteredOrganization", NULL, &type, (LPBYTE)path, &size);
    }

    if (*path)
    {
        buf[0] = 0;
        size = MAX_PATH;
        r = MsiGetPropertyA(hpkg, "COMPANYNAME", buf, &size);
        ok( r == ERROR_SUCCESS, "failed to get property: %d\n", r);
        ok( !lstrcmpA(buf, path), "Expected %s, got %s\n", path, buf);
    }

    buf[0] = 0;
    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "VersionDatabase", buf, &size);
    ok( r == ERROR_SUCCESS, "failed to get property: %d\n", r);
    trace("VersionDatabase = %s\n", buf);

    buf[0] = 0;
    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "VersionMsi", buf, &size);
    ok( r == ERROR_SUCCESS, "failed to get property: %d\n", r);
    trace("VersionMsi = %s\n", buf);

    buf[0] = 0;
    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "Date", buf, &size);
    ok( r == ERROR_SUCCESS, "failed to get property: %d\n", r);
    trace("Date = %s\n", buf);

    buf[0] = 0;
    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "Time", buf, &size);
    ok( r == ERROR_SUCCESS, "failed to get property: %d\n", r);
    trace("Time = %s\n", buf);

    buf[0] = 0;
    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "PackageCode", buf, &size);
    ok( r == ERROR_SUCCESS, "failed to get property: %d\n", r);
    trace("PackageCode = %s\n", buf);

    buf[0] = 0;
    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "ComputerName", buf, &size);
    ok( r == ERROR_SUCCESS, "Expected ERROR_SUCCESS got %d\n", r);
    trace("ComputerName = %s\n", buf);

    langid = GetUserDefaultLangID();
    sprintf(path, "%d", langid);

    buf[0] = 0;
    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "UserLanguageID", buf, &size);
    ok( r == ERROR_SUCCESS, "Expected ERROR_SUCCESS got %d\n", r);
    ok( !lstrcmpA(buf, path), "Expected \"%s\", got \"%s\"\n", path, buf);

    res = GetSystemMetrics(SM_CXSCREEN);
    buf[0] = 0;
    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "ScreenX", buf, &size);
    ok( r == ERROR_SUCCESS, "Expected ERROR_SUCCESS got %d\n", r);
    ok(atol(buf) == res, "Expected %d, got %ld\n", res, atol(buf));

    res = GetSystemMetrics(SM_CYSCREEN);
    buf[0] = 0;
    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "ScreenY", buf, &size);
    ok( r == ERROR_SUCCESS, "Expected ERROR_SUCCESS got %d\n", r);
    ok(atol(buf) == res, "Expected %d, got %ld\n", res, atol(buf));

    buf[0] = 0;
    size = MAX_PATH;
    r = MsiGetPropertyA(hpkg, "MsiNetAssemblySupport", buf, &size);
    if (r == ERROR_SUCCESS) trace( "MsiNetAssemblySupport \"%s\"\n", buf );

    if (pGetSystemInfo && pSHGetFolderPathA)
    {
        pGetSystemInfo(&si);
        if (S(U(si)).wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
        {
            buf[0] = 0;
            size = MAX_PATH;
            r = MsiGetPropertyA(hpkg, "Intel", buf, &size);
            ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
            ok(buf[0], "property not set\n");

            buf[0] = 0;
            size = MAX_PATH;
            r = MsiGetPropertyA(hpkg, "MsiAMD64", buf, &size);
            ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
            ok(buf[0], "property not set\n");

            buf[0] = 0;
            size = MAX_PATH;
            r = MsiGetPropertyA(hpkg, "Msix64", buf, &size);
            ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
            ok(buf[0], "property not set\n");

            buf[0] = 0;
            size = MAX_PATH;
            r = MsiGetPropertyA(hpkg, "System64Folder", buf, &size);
            ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
            GetSystemDirectoryA(path, MAX_PATH);
            if (size) buf[size - 1] = 0;
            ok(!lstrcmpiA(path, buf), "expected \"%s\", got \"%s\"\n", path, buf);

            buf[0] = 0;
            size = MAX_PATH;
            r = MsiGetPropertyA(hpkg, "SystemFolder", buf, &size);
            ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
            pGetSystemWow64DirectoryA(path, MAX_PATH);
            if (size) buf[size - 1] = 0;
            ok(!lstrcmpiA(path, buf), "expected \"%s\", got \"%s\"\n", path, buf);

            buf[0] = 0;
            size = MAX_PATH;
            r = MsiGetPropertyA(hpkg, "ProgramFiles64Folder", buf, &size);
            ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
            pSHGetFolderPathA(NULL, CSIDL_PROGRAM_FILES, NULL, 0, path);
            if (size) buf[size - 1] = 0;
            ok(!lstrcmpiA(path, buf), "expected \"%s\", got \"%s\"\n", path, buf);

            buf[0] = 0;
            size = MAX_PATH;
            r = MsiGetPropertyA(hpkg, "ProgramFilesFolder", buf, &size);
            ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
            pSHGetFolderPathA(NULL, CSIDL_PROGRAM_FILESX86, NULL, 0, path);
            if (size) buf[size - 1] = 0;
            ok(!lstrcmpiA(path, buf), "expected \"%s\", got \"%s\"\n", path, buf);

            buf[0] = 0;
            size = MAX_PATH;
            r = MsiGetPropertyA(hpkg, "CommonFiles64Folder", buf, &size);
            ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
            pSHGetFolderPathA(NULL, CSIDL_PROGRAM_FILES_COMMON, NULL, 0, path);
            if (size) buf[size - 1] = 0;
            ok(!lstrcmpiA(path, buf), "expected \"%s\", got \"%s\"\n", path, buf);

            buf[0] = 0;
            size = MAX_PATH;
            r = MsiGetPropertyA(hpkg, "CommonFilesFolder", buf, &size);
            ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
            pSHGetFolderPathA(NULL, CSIDL_PROGRAM_FILES_COMMONX86, NULL, 0, path);
            if (size) buf[size - 1] = 0;
            ok(!lstrcmpiA(path, buf), "expected \"%s\", got \"%s\"\n", path, buf);

            buf[0] = 0;
            size = MAX_PATH;
            r = MsiGetPropertyA(hpkg, "VersionNT64", buf, &size);
            ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
            ok(buf[0], "property not set\n");
        }
        else if (S(U(si)).wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
        {
            if (!is_wow64)
            {
                buf[0] = 0;
                size = MAX_PATH;
                r = MsiGetPropertyA(hpkg, "Intel", buf, &size);
                ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
                ok(buf[0], "property not set\n");

                buf[0] = 0;
                size = MAX_PATH;
                r = MsiGetPropertyA(hpkg, "MsiAMD64", buf, &size);
                ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
                ok(!buf[0], "property set\n");

                buf[0] = 0;
                size = MAX_PATH;
                r = MsiGetPropertyA(hpkg, "Msix64", buf, &size);
                ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
                ok(!buf[0], "property set\n");

                buf[0] = 0;
                size = MAX_PATH;
                r = MsiGetPropertyA(hpkg, "System64Folder", buf, &size);
                ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
                ok(!buf[0], "property set\n");

                buf[0] = 0;
                size = MAX_PATH;
                r = MsiGetPropertyA(hpkg, "SystemFolder", buf, &size);
                ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
                GetSystemDirectoryA(path, MAX_PATH);
                if (size) buf[size - 1] = 0;
                ok(!lstrcmpiA(path, buf), "expected \"%s\", got \"%s\"\n", path, buf);

                buf[0] = 0;
                size = MAX_PATH;
                r = MsiGetPropertyA(hpkg, "ProgramFiles64Folder", buf, &size);
                ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
                ok(!buf[0], "property set\n");

                buf[0] = 0;
                size = MAX_PATH;
                r = MsiGetPropertyA(hpkg, "ProgramFilesFolder", buf, &size);
                ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
                pSHGetFolderPathA(NULL, CSIDL_PROGRAM_FILES, NULL, 0, path);
                if (size) buf[size - 1] = 0;
                ok(!lstrcmpiA(path, buf), "expected \"%s\", got \"%s\"\n", path, buf);

                buf[0] = 0;
                size = MAX_PATH;
                r = MsiGetPropertyA(hpkg, "CommonFiles64Folder", buf, &size);
                ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
                ok(!buf[0], "property set\n");

                buf[0] = 0;
                size = MAX_PATH;
                r = MsiGetPropertyA(hpkg, "CommonFilesFolder", buf, &size);
                ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
                pSHGetFolderPathA(NULL, CSIDL_PROGRAM_FILES_COMMON, NULL, 0, path);
                if (size) buf[size - 1] = 0;
                ok(!lstrcmpiA(path, buf), "expected \"%s\", got \"%s\"\n", path, buf);

                buf[0] = 0;
                size = MAX_PATH;
                r = MsiGetPropertyA(hpkg, "VersionNT64", buf, &size);
                ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
                ok(!buf[0], "property set\n");
            }
            else
            {
                buf[0] = 0;
                size = MAX_PATH;
                r = MsiGetPropertyA(hpkg, "Intel", buf, &size);
                ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
                ok(buf[0], "property not set\n");

                buf[0] = 0;
                size = MAX_PATH;
                r = MsiGetPropertyA(hpkg, "MsiAMD64", buf, &size);
                ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
                ok(buf[0], "property not set\n");

                buf[0] = 0;
                size = MAX_PATH;
                r = MsiGetPropertyA(hpkg, "Msix64", buf, &size);
                ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
                ok(buf[0], "property not set\n");

                buf[0] = 0;
                size = MAX_PATH;
                r = MsiGetPropertyA(hpkg, "System64Folder", buf, &size);
                ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
                GetSystemDirectoryA(path, MAX_PATH);
                if (size) buf[size - 1] = 0;
                ok(!lstrcmpiA(path, buf), "expected \"%s\", got \"%s\"\n", path, buf);

                buf[0] = 0;
                size = MAX_PATH;
                r = MsiGetPropertyA(hpkg, "SystemFolder", buf, &size);
                ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
                pGetSystemWow64DirectoryA(path, MAX_PATH);
                if (size) buf[size - 1] = 0;
                ok(!lstrcmpiA(path, buf), "expected \"%s\", got \"%s\"\n", path, buf);

                buf[0] = 0;
                size = MAX_PATH;
                r = MsiGetPropertyA(hpkg, "ProgramFilesFolder64", buf, &size);
                ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
                ok(!buf[0], "property set\n");

                buf[0] = 0;
                size = MAX_PATH;
                r = MsiGetPropertyA(hpkg, "ProgramFilesFolder", buf, &size);
                ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
                pSHGetFolderPathA(NULL, CSIDL_PROGRAM_FILESX86, NULL, 0, path);
                if (size) buf[size - 1] = 0;
                ok(!lstrcmpiA(path, buf), "expected \"%s\", got \"%s\"\n", path, buf);

                buf[0] = 0;
                size = MAX_PATH;
                r = MsiGetPropertyA(hpkg, "CommonFilesFolder64", buf, &size);
                ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
                ok(!buf[0], "property set\n");

                buf[0] = 0;
                size = MAX_PATH;
                r = MsiGetPropertyA(hpkg, "CommonFilesFolder", buf, &size);
                ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
                pSHGetFolderPathA(NULL, CSIDL_PROGRAM_FILES_COMMONX86, NULL, 0, path);
                if (size) buf[size - 1] = 0;
                ok(!lstrcmpiA(path, buf), "expected \"%s\", got \"%s\"\n", path, buf);

                buf[0] = 0;
                size = MAX_PATH;
                r = MsiGetPropertyA(hpkg, "VersionNT64", buf, &size);
                ok(r == ERROR_SUCCESS, "failed to get property: %d\n", r);
                ok(buf[0], "property not set\n");
            }
        }
    }

    CloseHandle(hkey1);
    CloseHandle(hkey2);
    MsiCloseHandle(hpkg);
    DeleteFileA(msifile);
    MsiSetInternalUI(uilevel, NULL);
}