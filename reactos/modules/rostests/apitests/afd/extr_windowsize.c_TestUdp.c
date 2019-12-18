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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  addr ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  AFD_INFO_RECEIVE_WINDOW_SIZE ; 
 int /*<<< orphan*/  AFD_INFO_SEND_WINDOW_SIZE ; 
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AfdBind (int /*<<< orphan*/ ,struct sockaddr const*,int) ; 
 int /*<<< orphan*/  AfdCreateSocket (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AfdGetInformation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AfdSetInformation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_addr (char*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 

__attribute__((used)) static
void
TestUdp(void)
{
    NTSTATUS Status;
    HANDLE SocketHandle;
    struct sockaddr_in addr;
    ULONG OrigReceiveSize, OrigSendSize, ReceiveSize, SendSize;

    Status = AfdCreateSocket(&SocketHandle, AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    ok(Status == STATUS_SUCCESS, "AfdCreateSocket failed with %lx\n", Status);

    Status = AfdGetInformation(SocketHandle, AFD_INFO_RECEIVE_WINDOW_SIZE, NULL, &OrigReceiveSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdGetInformation failed with %lx\n", Status);
    ok(OrigReceiveSize == 0x1000 || OrigReceiveSize == 0x2000, "Invalid size: %lu\n", OrigReceiveSize);
    Status = AfdGetInformation(SocketHandle, AFD_INFO_SEND_WINDOW_SIZE, NULL, &OrigSendSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdGetInformation failed with %lx\n", Status);
    ok(OrigSendSize == 0x1000 || OrigSendSize == 0x2000, "Invalid size: %lu\n", OrigSendSize);

    ReceiveSize = 0;
    Status = AfdSetInformation(SocketHandle, AFD_INFO_RECEIVE_WINDOW_SIZE, NULL, &ReceiveSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdSetInformation failed with %lx\n", Status);
    SendSize = 0;
    Status = AfdSetInformation(SocketHandle, AFD_INFO_SEND_WINDOW_SIZE, NULL, &SendSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdSetInformation failed with %lx\n", Status);

    Status = AfdGetInformation(SocketHandle, AFD_INFO_RECEIVE_WINDOW_SIZE, NULL, &ReceiveSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdGetInformation failed with %lx\n", Status);
    ok(ReceiveSize == OrigReceiveSize, "Invalid size: %lu %lu\n", ReceiveSize, OrigReceiveSize);
    Status = AfdGetInformation(SocketHandle, AFD_INFO_SEND_WINDOW_SIZE, NULL, &SendSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdGetInformation failed with %lx\n", Status);
    ok(SendSize == OrigSendSize, "Invalid size: %lu %lu\n", SendSize, OrigSendSize);

    ReceiveSize = (ULONG)-1L;
    Status = AfdSetInformation(SocketHandle, AFD_INFO_RECEIVE_WINDOW_SIZE, NULL, &ReceiveSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdSetInformation failed with %lx\n", Status);
    SendSize = (ULONG)-1L;
    Status = AfdSetInformation(SocketHandle, AFD_INFO_SEND_WINDOW_SIZE, NULL, &SendSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdSetInformation failed with %lx\n", Status);

    Status = AfdGetInformation(SocketHandle, AFD_INFO_RECEIVE_WINDOW_SIZE, NULL, &ReceiveSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdGetInformation failed with %lx\n", Status);
    ok(ReceiveSize == OrigReceiveSize, "Invalid size: %lu %lu\n", ReceiveSize, OrigReceiveSize);
    Status = AfdGetInformation(SocketHandle, AFD_INFO_SEND_WINDOW_SIZE, NULL, &SendSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdGetInformation failed with %lx\n", Status);
    ok(SendSize == OrigSendSize, "Invalid size: %lu %lu\n", SendSize, OrigSendSize);

    ReceiveSize = OrigReceiveSize;
    Status = AfdSetInformation(SocketHandle, AFD_INFO_RECEIVE_WINDOW_SIZE, NULL, &ReceiveSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdSetInformation failed with %lx\n", Status);
    SendSize = OrigSendSize;
    Status = AfdSetInformation(SocketHandle, AFD_INFO_SEND_WINDOW_SIZE, NULL, &SendSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdSetInformation failed with %lx\n", Status);

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    addr.sin_port = htons(0);

    Status = AfdBind(SocketHandle, (const struct sockaddr *)&addr, sizeof(addr));
    ok(Status == STATUS_SUCCESS, "AfdBind failed with %lx\n", Status);

    Status = AfdGetInformation(SocketHandle, AFD_INFO_RECEIVE_WINDOW_SIZE, NULL, &ReceiveSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdGetInformation failed with %lx\n", Status);
    ok(ReceiveSize == OrigReceiveSize, "Invalid size: %lu %lu\n", ReceiveSize, OrigReceiveSize);
    Status = AfdGetInformation(SocketHandle, AFD_INFO_SEND_WINDOW_SIZE, NULL, &SendSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdGetInformation failed with %lx\n", Status);
    ok(SendSize == OrigSendSize, "Invalid size: %lu %lu\n", SendSize, OrigSendSize);

    ReceiveSize = 0;
    Status = AfdSetInformation(SocketHandle, AFD_INFO_RECEIVE_WINDOW_SIZE, NULL, &ReceiveSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdSetInformation failed with %lx\n", Status);
    SendSize = 0;
    Status = AfdSetInformation(SocketHandle, AFD_INFO_SEND_WINDOW_SIZE, NULL, &SendSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdSetInformation failed with %lx\n", Status);

    Status = AfdGetInformation(SocketHandle, AFD_INFO_RECEIVE_WINDOW_SIZE, NULL, &ReceiveSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdGetInformation failed with %lx\n", Status);
    ok(ReceiveSize == OrigReceiveSize, "Invalid size: %lu %lu\n", ReceiveSize, OrigReceiveSize);
    Status = AfdGetInformation(SocketHandle, AFD_INFO_SEND_WINDOW_SIZE, NULL, &SendSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdGetInformation failed with %lx\n", Status);
    ok(SendSize == OrigSendSize, "Invalid size: %lu %lu\n", SendSize, OrigSendSize);

    ReceiveSize = (ULONG)-1L;
    Status = AfdSetInformation(SocketHandle, AFD_INFO_RECEIVE_WINDOW_SIZE, NULL, &ReceiveSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdSetInformation failed with %lx\n", Status);
    SendSize = (ULONG)-1L;
    Status = AfdSetInformation(SocketHandle, AFD_INFO_SEND_WINDOW_SIZE, NULL, &SendSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdSetInformation failed with %lx\n", Status);

    Status = AfdGetInformation(SocketHandle, AFD_INFO_RECEIVE_WINDOW_SIZE, NULL, &ReceiveSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdGetInformation failed with %lx\n", Status);
    ok(ReceiveSize == OrigReceiveSize, "Invalid size: %lu %lu\n", ReceiveSize, OrigReceiveSize);
    Status = AfdGetInformation(SocketHandle, AFD_INFO_SEND_WINDOW_SIZE, NULL, &SendSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdGetInformation failed with %lx\n", Status);
    ok(SendSize == OrigSendSize, "Invalid size: %lu %lu\n", SendSize, OrigSendSize);

    ReceiveSize = OrigReceiveSize + 1;
    Status = AfdSetInformation(SocketHandle, AFD_INFO_RECEIVE_WINDOW_SIZE, NULL, &ReceiveSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdSetInformation failed with %lx\n", Status);
    SendSize = OrigSendSize + 1;
    Status = AfdSetInformation(SocketHandle, AFD_INFO_SEND_WINDOW_SIZE, NULL, &SendSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdSetInformation failed with %lx\n", Status);

    Status = AfdGetInformation(SocketHandle, AFD_INFO_RECEIVE_WINDOW_SIZE, NULL, &ReceiveSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdGetInformation failed with %lx\n", Status);
    ok(ReceiveSize == OrigReceiveSize, "Invalid size: %lu %lu\n", ReceiveSize, OrigReceiveSize);
    Status = AfdGetInformation(SocketHandle, AFD_INFO_SEND_WINDOW_SIZE, NULL, &SendSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdGetInformation failed with %lx\n", Status);
    ok(SendSize == OrigSendSize, "Invalid size: %lu %lu\n", SendSize, OrigSendSize);

    ReceiveSize = OrigReceiveSize - 1;
    Status = AfdSetInformation(SocketHandle, AFD_INFO_RECEIVE_WINDOW_SIZE, NULL, &ReceiveSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdSetInformation failed with %lx\n", Status);
    SendSize = OrigSendSize - 1;
    Status = AfdSetInformation(SocketHandle, AFD_INFO_SEND_WINDOW_SIZE, NULL, &SendSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdSetInformation failed with %lx\n", Status);

    Status = AfdGetInformation(SocketHandle, AFD_INFO_RECEIVE_WINDOW_SIZE, NULL, &ReceiveSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdGetInformation failed with %lx\n", Status);
    ok(ReceiveSize == OrigReceiveSize, "Invalid size: %lu %lu\n", ReceiveSize, OrigReceiveSize);
    Status = AfdGetInformation(SocketHandle, AFD_INFO_SEND_WINDOW_SIZE, NULL, &SendSize, NULL);
    ok(Status == STATUS_SUCCESS, "AfdGetInformation failed with %lx\n", Status);
    ok(SendSize == OrigSendSize, "Invalid size: %lu %lu\n", SendSize, OrigSendSize);

    NtClose(SocketHandle);
}