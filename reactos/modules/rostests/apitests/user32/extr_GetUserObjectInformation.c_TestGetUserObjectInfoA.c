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
typedef  int /*<<< orphan*/  UserObjectFlags ;
typedef  int /*<<< orphan*/  USEROBJECTFLAGS ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/ * PCHAR ;
typedef  int /*<<< orphan*/ * HWINSTA ;
typedef  int /*<<< orphan*/ * HDESK ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateGuarded (int) ; 
 int ERROR_INSUFFICIENT_BUFFER ; 
 int ERROR_INVALID_HANDLE ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_NOACCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FreeGuarded (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetCurrentThreadId () ; 
 int /*<<< orphan*/ * GetProcessWindowStation () ; 
 int /*<<< orphan*/ * GetThreadDesktop (int /*<<< orphan*/ ) ; 
 int NOTSET ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TestUserObjectInfo (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  TestUserObjectInfoWithString (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,char*) ; 
 int UOI_FLAGS ; 
 int UOI_NAME ; 
 int UOI_TYPE ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static
void
TestGetUserObjectInfoA(void)
{
    USEROBJECTFLAGS UserObjectFlags;
    PCHAR Buffer;
    ULONG BufferSize = 64;
    HDESK Desktop;
    HWINSTA WinSta;

    Buffer = AllocateGuarded(BufferSize);

    TestUserObjectInfo(NULL,    5,         NULL,             0,                       FALSE, ERROR_INVALID_HANDLE,      0);
    TestUserObjectInfo(NULL,    UOI_FLAGS, NULL,             0,                       FALSE, ERROR_INVALID_HANDLE,      0);
    TestUserObjectInfo(NULL,    UOI_FLAGS, (PVOID)1,         0,                       FALSE, ERROR_INVALID_HANDLE,      0);
    TestUserObjectInfo(NULL,    UOI_FLAGS, NULL,             1,                       FALSE, ERROR_NOACCESS,            NOTSET);
    TestUserObjectInfo(NULL,    UOI_FLAGS, (PVOID)1,         1,                       FALSE, ERROR_NOACCESS,            NOTSET);
    TestUserObjectInfo(NULL,    UOI_FLAGS, &UserObjectFlags, sizeof(UserObjectFlags), FALSE, ERROR_INVALID_HANDLE,      0);

    TestUserObjectInfo(NULL,    UOI_TYPE,  NULL,             0,                       FALSE, ERROR_INVALID_HANDLE,      0);
    TestUserObjectInfo(NULL,    UOI_TYPE,  (PVOID)1,         0,                       FALSE, ERROR_INVALID_HANDLE,      0);
    TestUserObjectInfo(NULL,    UOI_TYPE,  NULL,             1,                       FALSE, ERROR_INVALID_HANDLE,      0);
    TestUserObjectInfo(NULL,    UOI_TYPE,  (PVOID)1,         1,                       FALSE, ERROR_INVALID_HANDLE,      0);
    TestUserObjectInfo(NULL,    UOI_TYPE,  Buffer,           BufferSize,              FALSE, ERROR_INVALID_HANDLE,      0);

    TestUserObjectInfo(NULL,    UOI_NAME,  NULL,             0,                       FALSE, ERROR_INVALID_HANDLE,      0);
    TestUserObjectInfo(NULL,    UOI_NAME,  (PVOID)1,         0,                       FALSE, ERROR_INVALID_HANDLE,      0);
    TestUserObjectInfo(NULL,    UOI_NAME,  NULL,             1,                       FALSE, ERROR_INVALID_HANDLE,      0);
    TestUserObjectInfo(NULL,    UOI_NAME,  (PVOID)1,         1,                       FALSE, ERROR_INVALID_HANDLE,      0);
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
    TestUserObjectInfo(Desktop, UOI_FLAGS, (PVOID)1,         0,                       FALSE, ERROR_INSUFFICIENT_BUFFER, sizeof(USEROBJECTFLAGS));
    TestUserObjectInfo(Desktop, UOI_FLAGS, NULL,             1,                       FALSE, ERROR_NOACCESS,            NOTSET);
    TestUserObjectInfo(Desktop, UOI_FLAGS, (PVOID)1,         1,                       FALSE, ERROR_NOACCESS,            NOTSET);
    TestUserObjectInfo(Desktop, UOI_FLAGS, &UserObjectFlags, sizeof(UserObjectFlags), TRUE,  0xdeadbeef,                sizeof(USEROBJECTFLAGS));

    TestUserObjectInfoWithString(Desktop, UOI_TYPE, Buffer, BufferSize, "Desktop");
    TestUserObjectInfoWithString(Desktop, UOI_NAME, Buffer, BufferSize, "Default");

    TestUserObjectInfoWithString(WinSta,  UOI_TYPE, Buffer, BufferSize, "WindowStation");
    TestUserObjectInfoWithString(WinSta,  UOI_NAME, Buffer, BufferSize, "WinSta0");

    FreeGuarded(Buffer);

    /* Make sure nothing behind the needed buffer is touched */
    BufferSize = sizeof("Desktop");
    Buffer = AllocateGuarded(BufferSize);
    TestUserObjectInfo(Desktop, UOI_TYPE,  Buffer,           BufferSize,              TRUE,  0xdeadbeef,                sizeof("Desktop"));
    TestUserObjectInfo(Desktop, UOI_TYPE,  Buffer,           BufferSize + 1,          TRUE,  0xdeadbeef,                sizeof("Desktop"));
    FreeGuarded(Buffer);
}