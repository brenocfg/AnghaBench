#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_6__ {int Length; } ;
typedef  TYPE_1__ UNICODE_STRING ;
struct TYPE_7__ {int QuadPart; } ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  scalar_t__ NTSTATUS ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 scalar_t__ CreateFileA (char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_CREATE ; 
 int /*<<< orphan*/  FILE_PIPE_FULL_DUPLEX ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJ_CASE_INSENSITIVE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 scalar_t__ STATUS_INSTANCE_NOT_AVAILABLE ; 
 scalar_t__ STATUS_OBJECT_NAME_INVALID ; 
 scalar_t__ STATUS_OBJECT_NAME_NOT_FOUND ; 
 scalar_t__ STATUS_OBJECT_PATH_NOT_FOUND ; 
 scalar_t__ STATUS_PIPE_NOT_AVAILABLE ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  pNtClose (scalar_t__) ; 
 scalar_t__ pNtCreateNamedPipeFile (scalar_t__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,TYPE_2__*) ; 
 scalar_t__ pNtOpenFile (scalar_t__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pRtlInitUnicodeString (TYPE_1__*,char const*) ; 

__attribute__((used)) static void test_namespace_pipe(void)
{
    static const WCHAR buffer1[] = {'\\','?','?','\\','P','I','P','E','\\','t','e','s','t','\\','p','i','p','e',0};
    static const WCHAR buffer2[] = {'\\','?','?','\\','P','I','P','E','\\','T','E','S','T','\\','P','I','P','E',0};
    static const WCHAR buffer3[] = {'\\','?','?','\\','p','i','p','e','\\','t','e','s','t','\\','p','i','p','e',0};
    static const WCHAR buffer4[] = {'\\','?','?','\\','p','i','p','e','\\','t','e','s','t',0};
    OBJECT_ATTRIBUTES attr;
    UNICODE_STRING str;
    IO_STATUS_BLOCK iosb;
    NTSTATUS status;
    LARGE_INTEGER timeout;
    HANDLE pipe, h;

    timeout.QuadPart = -10000;

    pRtlInitUnicodeString(&str, buffer1);
    InitializeObjectAttributes(&attr, &str, 0, 0, NULL);
    status = pNtCreateNamedPipeFile(&pipe, GENERIC_READ|GENERIC_WRITE, &attr, &iosb, FILE_SHARE_READ|FILE_SHARE_WRITE,
                                    FILE_CREATE, FILE_PIPE_FULL_DUPLEX, FALSE, FALSE, FALSE, 1, 256, 256, &timeout);
    ok(status == STATUS_SUCCESS, "Failed to create NamedPipe(%08x)\n", status);

    status = pNtCreateNamedPipeFile(&pipe, GENERIC_READ|GENERIC_WRITE, &attr, &iosb, FILE_SHARE_READ|FILE_SHARE_WRITE,
                                    FILE_CREATE, FILE_PIPE_FULL_DUPLEX, FALSE, FALSE, FALSE, 1, 256, 256, &timeout);
    ok(status == STATUS_INSTANCE_NOT_AVAILABLE,
        "NtCreateNamedPipeFile should have failed with STATUS_INSTANCE_NOT_AVAILABLE got(%08x)\n", status);

    pRtlInitUnicodeString(&str, buffer2);
    InitializeObjectAttributes(&attr, &str, 0, 0, NULL);
    status = pNtCreateNamedPipeFile(&pipe, GENERIC_READ|GENERIC_WRITE, &attr, &iosb, FILE_SHARE_READ|FILE_SHARE_WRITE,
                                    FILE_CREATE, FILE_PIPE_FULL_DUPLEX, FALSE, FALSE, FALSE, 1, 256, 256, &timeout);
    ok(status == STATUS_INSTANCE_NOT_AVAILABLE,
        "NtCreateNamedPipeFile should have failed with STATUS_INSTANCE_NOT_AVAILABLE got(%08x)\n", status);

    h = CreateFileA("\\\\.\\pipe\\test\\pipe", GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL,
                    OPEN_EXISTING, 0, 0 );
    ok(h != INVALID_HANDLE_VALUE, "Failed to open NamedPipe (%u)\n", GetLastError());
    pNtClose(h);

    pRtlInitUnicodeString(&str, buffer3);
    InitializeObjectAttributes(&attr, &str, 0, 0, NULL);
    status = pNtOpenFile(&h, GENERIC_READ, &attr, &iosb, FILE_SHARE_READ|FILE_SHARE_WRITE, 0);
    ok(status == STATUS_OBJECT_PATH_NOT_FOUND ||
       status == STATUS_PIPE_NOT_AVAILABLE ||
       status == STATUS_OBJECT_NAME_INVALID || /* vista */
       status == STATUS_OBJECT_NAME_NOT_FOUND, /* win8 */
        "NtOpenFile should have failed with STATUS_OBJECT_PATH_NOT_FOUND got(%08x)\n", status);

    pRtlInitUnicodeString(&str, buffer4);
    InitializeObjectAttributes(&attr, &str, OBJ_CASE_INSENSITIVE, 0, NULL);
    status = pNtOpenFile(&h, GENERIC_READ, &attr, &iosb, FILE_SHARE_READ|FILE_SHARE_WRITE, 0);
    ok(status == STATUS_OBJECT_NAME_NOT_FOUND ||
       status == STATUS_OBJECT_NAME_INVALID, /* vista */
        "NtOpenFile should have failed with STATUS_OBJECT_NAME_NOT_FOUND got(%08x)\n", status);

    str.Length -= 4 * sizeof(WCHAR);
    status = pNtOpenFile(&h, GENERIC_READ, &attr, &iosb, FILE_SHARE_READ|FILE_SHARE_WRITE, 0);
    ok(status == STATUS_SUCCESS, "NtOpenFile should have succeeded got %08x\n", status);
    pNtClose( h );

    str.Length -= sizeof(WCHAR);
    status = pNtOpenFile(&h, GENERIC_READ, &attr, &iosb, FILE_SHARE_READ|FILE_SHARE_WRITE, 0);
    ok(status == STATUS_SUCCESS, "NtOpenFile should have succeeded got %08x\n", status);
    pNtClose( h );

    pNtClose(pipe);
}