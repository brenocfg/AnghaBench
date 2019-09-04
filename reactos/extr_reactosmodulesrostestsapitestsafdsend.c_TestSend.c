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
struct TYPE_2__ {void* s_addr; } ;
struct sockaddr_in {void* sin_port; TYPE_1__ sin_addr; void* sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  addr ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 void* AF_INET ; 
 scalar_t__ AfdBind (int /*<<< orphan*/ ,struct sockaddr const*,int) ; 
 scalar_t__ AfdConnect (int /*<<< orphan*/ ,struct sockaddr const*,int) ; 
 scalar_t__ AfdCreateSocket (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ AfdSend (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlZeroMemory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ STATUS_INVALID_CONNECTION ; 
 scalar_t__ STATUS_SUCCESS ; 
 void* htons (int) ; 
 void* inet_addr (char*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static
void
TestSend(void)
{
    NTSTATUS Status;
    HANDLE SocketHandle;
    CHAR Buffer[32];
    struct sockaddr_in addr;

    RtlZeroMemory(Buffer, sizeof(Buffer));

    Status = AfdCreateSocket(&SocketHandle, AF_INET, SOCK_STREAM, IPPROTO_TCP);
    ok(Status == STATUS_SUCCESS, "AfdCreateSocket failed with %lx\n", Status);

    Status = AfdSend(SocketHandle, NULL, 0);
    ok(Status == STATUS_INVALID_CONNECTION, "AfdSend failed with %lx\n", Status);

    Status = AfdSend(SocketHandle, Buffer, sizeof(Buffer));
    ok(Status == STATUS_INVALID_CONNECTION, "AfdSend failed with %lx\n", Status);

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    addr.sin_port = htons(0);

    Status = AfdBind(SocketHandle, (const struct sockaddr *)&addr, sizeof(addr));
    ok(Status == STATUS_SUCCESS, "AfdBind failed with %lx\n", Status);

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("8.8.8.8");
    addr.sin_port = htons(53);

    Status = AfdConnect(SocketHandle, (const struct sockaddr *)&addr, sizeof(addr));
    ok(Status == STATUS_SUCCESS, "AfdConnect failed with %lx\n", Status);

    Status = AfdSend(SocketHandle, NULL, 0);
    ok(Status == STATUS_SUCCESS, "AfdSend failed with %lx\n", Status);

    Status = AfdSend(SocketHandle, Buffer, sizeof(Buffer));
    ok(Status == STATUS_SUCCESS, "AfdSend failed with %lx\n", Status);

    NtClose(SocketHandle);
}