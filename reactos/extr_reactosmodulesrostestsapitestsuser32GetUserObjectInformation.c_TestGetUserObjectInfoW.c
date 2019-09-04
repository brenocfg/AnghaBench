#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WinStaName ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UserObjectFlags ;
typedef  int /*<<< orphan*/  USEROBJECTFLAGS ;
typedef  int ULONG ;
struct TYPE_4__ {int /*<<< orphan*/  LowPart; int /*<<< orphan*/  HighPart; } ;
struct TYPE_5__ {TYPE_1__ AuthenticationId; } ;
typedef  TYPE_2__ TOKEN_STATISTICS ;
typedef  int /*<<< orphan*/  Statistics ;
typedef  int /*<<< orphan*/ * PWCHAR ;
typedef  int /*<<< orphan*/ * HWINSTA ;
typedef  int /*<<< orphan*/ * HDESK ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateGuarded (int) ; 
 int /*<<< orphan*/  CloseDesktop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloseWindowStation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateDesktopW (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateWindowStationW (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int DESKTOP_CREATEWINDOW ; 
 int DESKTOP_READOBJECTS ; 
 int ERROR_INSUFFICIENT_BUFFER ; 
 int ERROR_INVALID_HANDLE ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_NOACCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FreeGuarded (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  GetCurrentThreadId () ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/ * GetProcessWindowStation () ; 
 int /*<<< orphan*/ * GetThreadDesktop (int /*<<< orphan*/ ) ; 
 scalar_t__ GetTokenInformation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int,int*) ; 
 int NOTSET ; 
 scalar_t__ OpenProcessToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StringCbCopyW (char*,int,char*) ; 
 int /*<<< orphan*/  StringCbPrintfW (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOKEN_QUERY ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  TestUserObjectInfo (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,scalar_t__,int,int) ; 
 int /*<<< orphan*/  TestUserObjectInfoWithString (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  TokenStatistics ; 
 int UOI_FLAGS ; 
 int UOI_NAME ; 
 int UOI_TYPE ; 
 int /*<<< orphan*/ * UlongToPtr (int) ; 
 int /*<<< orphan*/  WINSTA_READATTRIBUTES ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static
void
TestGetUserObjectInfoW(void)
{
    USEROBJECTFLAGS UserObjectFlags;
    PWCHAR Buffer;
    ULONG BufferSize = 64 * sizeof(WCHAR);
    HDESK Desktop;
    HDESK Desktop2;
    HWINSTA WinSta;
    HANDLE Token;
    TOKEN_STATISTICS Statistics;
    WCHAR WinStaName[64];
    BOOL Success;
    ULONG Length;

    Buffer = AllocateGuarded(BufferSize);

    TestUserObjectInfo(NULL,    5,         NULL,             0,                       FALSE, ERROR_INVALID_HANDLE,      0);
    TestUserObjectInfo(NULL,    UOI_FLAGS, NULL,             0,                       FALSE, ERROR_INVALID_HANDLE,      0);
    TestUserObjectInfo(NULL,    UOI_FLAGS, UlongToPtr(1),    0,                       FALSE, ERROR_INVALID_HANDLE,      0);
    TestUserObjectInfo(NULL,    UOI_FLAGS, NULL,             1,                       FALSE, ERROR_NOACCESS,            NOTSET);
    TestUserObjectInfo(NULL,    UOI_FLAGS, UlongToPtr(1),    1,                       FALSE, ERROR_NOACCESS,            NOTSET);
    TestUserObjectInfo(NULL,    UOI_FLAGS, &UserObjectFlags, sizeof(UserObjectFlags), FALSE, ERROR_INVALID_HANDLE,      0);

    TestUserObjectInfo(NULL,    UOI_TYPE,  NULL,             0,                       FALSE, ERROR_INVALID_HANDLE,      0);
    TestUserObjectInfo(NULL,    UOI_TYPE,  UlongToPtr(1),    0,                       FALSE, ERROR_INVALID_HANDLE,      0);
    TestUserObjectInfo(NULL,    UOI_TYPE,  NULL,             1,                       FALSE, ERROR_NOACCESS,            NOTSET);
    TestUserObjectInfo(NULL,    UOI_TYPE,  UlongToPtr(1),    1,                       FALSE, ERROR_NOACCESS,            NOTSET);
    TestUserObjectInfo(NULL,    UOI_TYPE,  Buffer,           BufferSize,              FALSE, ERROR_INVALID_HANDLE,      0);

    TestUserObjectInfo(NULL,    UOI_NAME,  NULL,             0,                       FALSE, ERROR_INVALID_HANDLE,      0);
    TestUserObjectInfo(NULL,    UOI_NAME,  UlongToPtr(1),    0,                       FALSE, ERROR_INVALID_HANDLE,      0);
    TestUserObjectInfo(NULL,    UOI_NAME,  NULL,             1,                       FALSE, ERROR_NOACCESS,            NOTSET);
    TestUserObjectInfo(NULL,    UOI_NAME,  UlongToPtr(1),    1,                       FALSE, ERROR_NOACCESS,            NOTSET);
    TestUserObjectInfo(NULL,    UOI_NAME,  Buffer,           BufferSize,              FALSE, ERROR_INVALID_HANDLE,      0);

    Desktop = GetThreadDesktop(GetCurrentThreadId());
    if (!Desktop)
    {
        skip("Failed to get desktop handle\n");
        FreeGuarded(Buffer);
        return;
    }

    WinSta = GetProcessWindowStation();
    if (!WinSta)
    {
        skip("Failed to get winsta handle\n");
        FreeGuarded(Buffer);
        return;
    }

    TestUserObjectInfo(Desktop, 5,         NULL,             0,                       FALSE, ERROR_INVALID_PARAMETER,   0);
    TestUserObjectInfo(Desktop, UOI_FLAGS, NULL,             0,                       FALSE, ERROR_INSUFFICIENT_BUFFER, sizeof(USEROBJECTFLAGS));
    TestUserObjectInfo(Desktop, UOI_FLAGS, UlongToPtr(1),    0,                       FALSE, ERROR_INSUFFICIENT_BUFFER, sizeof(USEROBJECTFLAGS));
    TestUserObjectInfo(Desktop, UOI_FLAGS, NULL,             1,                       FALSE, ERROR_NOACCESS,            NOTSET);
    TestUserObjectInfo(Desktop, UOI_FLAGS, UlongToPtr(1),    1,                       FALSE, ERROR_NOACCESS,            NOTSET);
    TestUserObjectInfo(Desktop, UOI_FLAGS, &UserObjectFlags, sizeof(UserObjectFlags), TRUE,  0xdeadbeef,                sizeof(USEROBJECTFLAGS));

    TestUserObjectInfoWithString(Desktop, UOI_TYPE, Buffer, BufferSize, L"Desktop");
    TestUserObjectInfoWithString(Desktop, UOI_NAME, Buffer, BufferSize, L"Default");

    TestUserObjectInfoWithString(WinSta, UOI_TYPE, Buffer, BufferSize, L"WindowStation");
    TestUserObjectInfoWithString(WinSta, UOI_NAME, Buffer, BufferSize, L"WinSta0");

    /* Autogenerated name will be Service-0x<luidhigh>-<luidlow>$ */
    StringCbCopyW(WinStaName, sizeof(WinStaName), L"<failed>");
    Success = OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &Token);
    ok(Success == TRUE, "OpenProcessToken failed with %lu\n", GetLastError());
    if (Success)
    {
        Success = GetTokenInformation(Token,
                                      TokenStatistics,
                                      &Statistics,
                                      sizeof(Statistics),
                                      &Length);
        ok(Success == TRUE, "GetTokenInformation failed with %lu\n", GetLastError());
        if (Success)
        {
            StringCbPrintfW(WinStaName,
                            sizeof(WinStaName),
                            L"Service-0x%lx-%lx$",
                            Statistics.AuthenticationId.HighPart,
                            Statistics.AuthenticationId.LowPart);
            trace("Expected autogenerated Winsta name: %ls\n", WinStaName);
        }
        CloseHandle(Token);
    }

    /* Create our own Winsta */
    WinSta = CreateWindowStationW(NULL, 0, WINSTA_READATTRIBUTES, NULL);
    ok(WinSta != NULL, "CreateWindowStationW failed with %lu\n", GetLastError());
    if (WinSta)
    {
        TestUserObjectInfoWithString(WinSta, UOI_TYPE, Buffer, BufferSize, L"WindowStation");
        TestUserObjectInfoWithString(WinSta, UOI_NAME, Buffer, BufferSize, WinStaName);
        CloseWindowStation(WinSta);
    }
    else
    {
        skip("Failed to create winsta\n");
    }

    WinSta = CreateWindowStationW(L"", 0, WINSTA_READATTRIBUTES, NULL);
    ok(WinSta != NULL, "CreateWindowStationW failed with %lu\n", GetLastError());
    if (WinSta)
    {
        TestUserObjectInfoWithString(WinSta, UOI_TYPE, Buffer, BufferSize, L"WindowStation");
        TestUserObjectInfoWithString(WinSta, UOI_NAME, Buffer, BufferSize, WinStaName);
        CloseWindowStation(WinSta);
    }
    else
    {
        skip("Failed to create winsta\n");
    }

    WinSta = CreateWindowStationW(L"GetUserObjectInformation_apitest_winsta", 0, WINSTA_READATTRIBUTES, NULL);
    ok(WinSta != NULL, "CreateWindowStationW failed with %lu\n", GetLastError());
    if (WinSta)
    {
        TestUserObjectInfoWithString(WinSta, UOI_TYPE, Buffer, BufferSize, L"WindowStation");
        TestUserObjectInfoWithString(WinSta, UOI_NAME, Buffer, BufferSize, L"GetUserObjectInformation_apitest_winsta");
        CloseWindowStation(WinSta);
    }
    else
    {
        skip("Failed to create winsta\n");
    }

    WinSta = CreateWindowStationW(L"1", 0, WINSTA_READATTRIBUTES, NULL);
    ok(WinSta != NULL, "CreateWindowStationW failed with %lu\n", GetLastError());
    if (WinSta)
    {
        TestUserObjectInfoWithString(WinSta, UOI_TYPE, Buffer, BufferSize, L"WindowStation");
        TestUserObjectInfoWithString(WinSta, UOI_NAME, Buffer, BufferSize, L"1");
        CloseWindowStation(WinSta);
    }
    else
    {
        skip("Failed to create winsta\n");
    }

    /* Create our own desktop */
    Desktop2 = CreateDesktopW(NULL, NULL, NULL, 0, DESKTOP_CREATEWINDOW | DESKTOP_READOBJECTS, NULL);
    ok(Desktop2 == NULL, "CreateDesktopW succeeded\n");
    if (Desktop2) CloseDesktop(Desktop2);

    Desktop2 = CreateDesktopW(L"", NULL, NULL, 0, DESKTOP_CREATEWINDOW | DESKTOP_READOBJECTS, NULL);
    ok(Desktop2 == NULL, "CreateDesktopW succeeded\n");
    if (Desktop2) CloseDesktop(Desktop2);

    Desktop2 = CreateDesktopW(L"2", NULL, NULL, 0, DESKTOP_CREATEWINDOW | DESKTOP_READOBJECTS, NULL);
    ok(Desktop2 != NULL, "CreateDesktopW failed with %lu\n", GetLastError());
    if (Desktop2)
    {
        TestUserObjectInfoWithString(Desktop2, UOI_TYPE, Buffer, BufferSize, L"Desktop");
        TestUserObjectInfoWithString(Desktop2, UOI_NAME, Buffer, BufferSize, L"2");
    }
    else
    {
        skip("Failed to create winsta\n");
    }

    CloseDesktop(Desktop2);

    FreeGuarded(Buffer);

    /* Make sure nothing behind the needed buffer is touched */
    BufferSize = sizeof(L"Desktop");
    Buffer = AllocateGuarded(BufferSize);
    TestUserObjectInfo(Desktop, UOI_TYPE,  Buffer,           BufferSize,              TRUE,  0xdeadbeef,                sizeof(L"Desktop"));
    TestUserObjectInfo(Desktop, UOI_TYPE,  Buffer,           BufferSize + 1,          FALSE, ERROR_NOACCESS,            NOTSET);
    FreeGuarded(Buffer);
}