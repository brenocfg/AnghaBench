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
typedef  char WCHAR ;
struct TYPE_3__ {int dwOSVersionInfoSize; char* szCSDVersion; int dwPlatformId; int dwMajorVersion; int dwMinorVersion; int wSuiteMask; int dwBuildNumber; int /*<<< orphan*/  wProductType; } ;
typedef  int /*<<< orphan*/  OSVERSIONINFOW ;
typedef  TYPE_1__ OSVERSIONINFOEXW ;
typedef  int /*<<< orphan*/  OSVERSIONINFO ;
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int BUFSIZE ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 scalar_t__ GetVersionExW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegQueryValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  VER_NT_DOMAIN_CONTROLLER ; 
 int /*<<< orphan*/  VER_NT_SERVER ; 
 int /*<<< orphan*/  VER_NT_WORKSTATION ; 
#define  VER_PLATFORM_WIN32_NT 130 
#define  VER_PLATFORM_WIN32_WINDOWS 129 
#define  VER_PLATFORM_WIN32s 128 
 int VER_SUITE_BLADE ; 
 int VER_SUITE_DATACENTER ; 
 int VER_SUITE_ENTERPRISE ; 
 int VER_SUITE_PERSONAL ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 scalar_t__ _wcsnicmp (char*,char*,int) ; 
 int /*<<< orphan*/  lstrcmpiW (char*,char*) ; 
 int wcslen (char*) ; 
 int /*<<< orphan*/  wprintf (char*,...) ; 

__attribute__((used)) static void
PrintOSVersion(void)
{
#define BUFSIZE 160
  OSVERSIONINFOEXW VersionInfo;
  BOOL OsVersionInfoEx;
  HKEY hKey;
  WCHAR ProductType[BUFSIZE];
  DWORD BufLen;
  LONG Ret;
  unsigned RosVersionLen;
  LPWSTR RosVersion;

  /* Try calling GetVersionEx using the OSVERSIONINFOEX structure.
   * If that fails, try using the OSVERSIONINFO structure. */

  ZeroMemory(&VersionInfo, sizeof(OSVERSIONINFOEXW));
  VersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXW);

  OsVersionInfoEx = GetVersionExW((OSVERSIONINFOW *) &VersionInfo);
  if (! OsVersionInfoEx)
    {
      VersionInfo.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
      if (! GetVersionExW((OSVERSIONINFOW *) &VersionInfo))
        {
          return;
        }
    }

  RosVersion = VersionInfo.szCSDVersion + wcslen(VersionInfo.szCSDVersion) + 1;
  RosVersionLen = sizeof(VersionInfo.szCSDVersion) / sizeof(VersionInfo.szCSDVersion[0]) -
                  (RosVersion - VersionInfo.szCSDVersion);
  if (7 <= RosVersionLen && 0 == _wcsnicmp(RosVersion, L"ReactOS", 7))
    {
      wprintf(L"Running on %s\n", RosVersion);
      return;
    }

  switch (VersionInfo.dwPlatformId)
    {
      /* Test for the Windows NT product family. */
      case VER_PLATFORM_WIN32_NT:

        /* Test for the specific product. */
        if (5 == VersionInfo.dwMajorVersion && 2 == VersionInfo.dwMinorVersion)
          {
            wprintf(L"Running on Microsoft Windows Server 2003, ");
          }
        else if (5 == VersionInfo.dwMajorVersion && 1 == VersionInfo.dwMinorVersion)
          {
            wprintf(L"Running on Microsoft Windows XP ");
          }
        else if (5 == VersionInfo.dwMajorVersion && 0 == VersionInfo.dwMinorVersion)
          {
            wprintf(L"Running on Microsoft Windows 2000 ");
          }
        else if (VersionInfo.dwMajorVersion <= 4 )
          {
            wprintf(L"Running on Microsoft Windows NT ");
          }

        /* Test for specific product on Windows NT 4.0 SP6 and later. */
        if (OsVersionInfoEx)
          {
            /* Test for the workstation type. */
            if (VER_NT_WORKSTATION == VersionInfo.wProductType)
              {
                if (4 == VersionInfo.dwMajorVersion)
                  {
                    wprintf(L"Workstation 4.0 ");
                  }
                else if (0 != (VersionInfo.wSuiteMask & VER_SUITE_PERSONAL))
                  {
                    wprintf(L"Home Edition ");
                  }
                else
                  {
                    wprintf(L"Professional ");
                  }
              }

            /* Test for the server type. */
            else if (VER_NT_SERVER == VersionInfo.wProductType  ||
                     VER_NT_DOMAIN_CONTROLLER == VersionInfo.wProductType)
              {
                if (5 == VersionInfo.dwMajorVersion && 2 == VersionInfo.dwMinorVersion)
                  {
                    if (0 != (VersionInfo.wSuiteMask & VER_SUITE_DATACENTER))
                      {
                        wprintf(L"Datacenter Edition ");
                      }
                    else if (0 != (VersionInfo.wSuiteMask & VER_SUITE_ENTERPRISE))
                      {
                        wprintf(L"Enterprise Edition ");
                      }
                    else if (VER_SUITE_BLADE == VersionInfo.wSuiteMask)
                      {
                        wprintf(L"Web Edition ");
                      }
                    else
                      {
                        wprintf(L"Standard Edition ");
                      }
                  }

                else if (5 == VersionInfo.dwMajorVersion && 0 == VersionInfo.dwMinorVersion)
                  {
                    if (0 != (VersionInfo.wSuiteMask & VER_SUITE_DATACENTER))
                      {
                        wprintf(L"Datacenter Server ");
                      }
                    else if (0 != (VersionInfo.wSuiteMask & VER_SUITE_ENTERPRISE))
                      {
                        wprintf(L"Advanced Server " );
                      }
                    else
                      {
                        wprintf(L"Server " );
                      }
                  }

                else  /* Windows NT 4.0 */
                  {
                    if (0 != (VersionInfo.wSuiteMask & VER_SUITE_ENTERPRISE))
                      {
                        wprintf(L"Server 4.0, Enterprise Edition ");
                      }
                    else
                      {
                        wprintf(L"Server 4.0 ");
                      }
                  }
              }
          }
        else  /* Test for specific product on Windows NT 4.0 SP5 and earlier */
          {
            BufLen = BUFSIZE;

            Ret = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                                L"SYSTEM\\CurrentControlSet\\Control\\ProductOptions",
                                0, KEY_QUERY_VALUE, &hKey);
            if (ERROR_SUCCESS != Ret)
              {
                return;
              }

            Ret = RegQueryValueExW(hKey, L"ProductType", NULL, NULL,
                                   (LPBYTE) ProductType, &BufLen);
            if (ERROR_SUCCESS != Ret || BUFSIZE < BufLen)
              {
                return;
              }

            RegCloseKey(hKey);

            if (0 == lstrcmpiW(L"WINNT", ProductType))
              {
                wprintf(L"Workstation ");
              }
            else if (0 == lstrcmpiW(L"LANMANNT", ProductType))
              {
                wprintf(L"Server ");
              }
            else if (0 == lstrcmpiW(L"SERVERNT", ProductType))
              {
                wprintf(L"Advanced Server ");
              }

            wprintf(L"%d.%d ", VersionInfo.dwMajorVersion, VersionInfo.dwMinorVersion);
          }

        /* Display service pack (if any) and build number. */

        if (4 == VersionInfo.dwMajorVersion &&
            0 == lstrcmpiW(VersionInfo.szCSDVersion, L"Service Pack 6"))
          {
            /* Test for SP6 versus SP6a. */
            Ret = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                                L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Hotfix\\Q246009",
                                0, KEY_QUERY_VALUE, &hKey);
            if (ERROR_SUCCESS == Ret)
              {
                wprintf(L"Service Pack 6a (Build %d)\n", VersionInfo.dwBuildNumber & 0xFFFF);
              }
            else /* Windows NT 4.0 prior to SP6a */
              {
                wprintf(L"%s (Build %d)\n",
                        VersionInfo.szCSDVersion,
                        VersionInfo.dwBuildNumber & 0xFFFF);
              }

            RegCloseKey(hKey);
          }
        else /* not Windows NT 4.0 */
          {
            wprintf(L"%s (Build %d)\n",
                    VersionInfo.szCSDVersion,
                    VersionInfo.dwBuildNumber & 0xFFFF);
          }


        break;

      /* Test for the Windows Me/98/95. A bit silly since we're using Unicode... */
      case VER_PLATFORM_WIN32_WINDOWS:

        if (4 == VersionInfo.dwMajorVersion && 0 == VersionInfo.dwMinorVersion)
          {
            wprintf(L"Running on Microsoft Windows 95 ");
            if (L'C' == VersionInfo.szCSDVersion[1] || L'B' == VersionInfo.szCSDVersion[1])
              {
                wprintf(L"OSR2");
              }
          }

        else if (4 == VersionInfo.dwMajorVersion && 10 == VersionInfo.dwMinorVersion)
          {
            wprintf(L"Running on Microsoft Windows 98 ");
            if (L'A' == VersionInfo.szCSDVersion[1])
              {
                wprintf(L"SE");
              }
          }

        else if (4 == VersionInfo.dwMajorVersion && 90 == VersionInfo.dwMinorVersion)
          {
            wprintf(L"Running on Microsoft Windows Millennium Edition");
          }
        wprintf(L"\n");
        break;

      case VER_PLATFORM_WIN32s: /* Even silier... */

        wprintf(L"Running on Microsoft Win32s\n");
        break;
    }
}