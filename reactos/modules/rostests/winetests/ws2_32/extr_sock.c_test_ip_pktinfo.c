#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yes ;
struct TYPE_22__ {scalar_t__ s_addr; } ;
struct sockaddr_in {TYPE_3__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_20__ {scalar_t__ s_addr; } ;
struct in_pktinfo {TYPE_1__ ipi_addr; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  s3addr ;
typedef  int /*<<< orphan*/  s2addr ;
typedef  int /*<<< orphan*/  s1addr ;
typedef  int /*<<< orphan*/  recvbuf ;
typedef  int /*<<< orphan*/  pktbuf ;
typedef  int /*<<< orphan*/  pWSARecvMsg ;
typedef  int /*<<< orphan*/  ov ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  hdr ;
typedef  int /*<<< orphan*/  addresses ;
typedef  int /*<<< orphan*/  WSARecvMsg_GUID ;
struct TYPE_21__ {char* buf; int len; } ;
struct TYPE_23__ {scalar_t__ hEvent; int namelen; int dwBufferCount; int dwFlags; TYPE_2__ Control; TYPE_7__* lpBuffers; struct sockaddr* name; } ;
typedef  TYPE_4__ WSAOVERLAPPED ;
typedef  TYPE_4__ WSAMSG ;
struct TYPE_24__ {scalar_t__ cmsg_level; scalar_t__ cmsg_type; } ;
typedef  TYPE_6__ WSACMSGHDR ;
struct TYPE_25__ {char* buf; int len; } ;
typedef  TYPE_7__ WSABUF ;
typedef  void* ULONG ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  scalar_t__ SOCKET ;
typedef  unsigned int (* LPFN_WSARECVMSG ) (scalar_t__,TYPE_4__*,int*,TYPE_4__*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateEventA (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ INVALID_SOCKET ; 
 scalar_t__ IPPROTO_IP ; 
 scalar_t__ IP_PKTINFO ; 
 int IP_PKTINFO_LEN ; 
 int MSG_CTRUNC ; 
 int /*<<< orphan*/  SIO_GET_EXTENSION_FUNCTION_POINTER ; 
 unsigned int SOCKET_ERROR ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int TRUE ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 int WSAEFAULT ; 
 int WSAEMSGSIZE ; 
 int WSAGetLastError () ; 
 int /*<<< orphan*/  WSAGetOverlappedResult (scalar_t__,TYPE_4__*,int*,int,int*) ; 
 int /*<<< orphan*/  WSAID_WSARECVMSG ; 
 int /*<<< orphan*/  WSAIoctl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,unsigned int (*) (scalar_t__,TYPE_4__*,int*,TYPE_4__*,int /*<<< orphan*/ *),int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ WSA_CMSG_DATA (TYPE_6__*) ; 
 TYPE_6__* WSA_CMSG_FIRSTHDR (TYPE_4__*) ; 
 TYPE_6__* WSA_CMSG_NXTHDR (TYPE_4__*,TYPE_6__*) ; 
 int WSA_IO_PENDING ; 
 scalar_t__ WaitForSingleObject (scalar_t__,int) ; 
 unsigned int bind (scalar_t__,struct sockaddr*,int) ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 scalar_t__ getsockname (scalar_t__,struct sockaddr*,int*) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 void* inet_addr (char*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 unsigned int sendto (scalar_t__,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 unsigned int setsockopt (scalar_t__,scalar_t__,scalar_t__,char const*,int) ; 
 int /*<<< orphan*/  skip (char*,...) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_ip_pktinfo(void)
{
    ULONG addresses[2] = {inet_addr("127.0.0.1"), htonl(INADDR_ANY)};
    char recvbuf[10], pktbuf[512], msg[] = "HELLO";
    struct sockaddr_in s1addr, s2addr, s3addr;
    GUID WSARecvMsg_GUID = WSAID_WSARECVMSG;
    LPFN_WSARECVMSG pWSARecvMsg = NULL;
    unsigned int rc, yes = 1;
    BOOL foundhdr;
    DWORD dwBytes, dwSize, dwFlags;
    socklen_t addrlen;
    WSACMSGHDR *cmsg;
    WSAOVERLAPPED ov;
    WSABUF iovec[1];
    SOCKET s1, s2;
    WSAMSG hdr;
    int i, err;

    memset(&ov, 0, sizeof(ov));
    ov.hEvent = CreateEventA(NULL, FALSE, FALSE, NULL);
    if (ov.hEvent == INVALID_HANDLE_VALUE)
    {
        skip("Could not create event object, some tests will be skipped. errno = %d\n", GetLastError());
        return;
    }

    memset(&hdr, 0x00, sizeof(hdr));
    s1addr.sin_family = AF_INET;
    s1addr.sin_port   = htons(0);
    /* Note: s1addr.sin_addr is set below */
    iovec[0].buf      = recvbuf;
    iovec[0].len      = sizeof(recvbuf);
    hdr.name          = (struct sockaddr*)&s3addr;
    hdr.namelen       = sizeof(s3addr);
    hdr.lpBuffers     = &iovec[0];
    hdr.dwBufferCount = 1;
    hdr.Control.buf   = pktbuf;
    /* Note: hdr.Control.len is set below */
    hdr.dwFlags       = 0;

    for (i=0;i<sizeof(addresses)/sizeof(UINT32);i++)
    {
        s1addr.sin_addr.s_addr = addresses[i];

        /* Build "server" side socket */
        s1=socket(AF_INET, SOCK_DGRAM, 0);
        if (s1 == INVALID_SOCKET)
        {
            skip("socket() failed error, some tests skipped: %d\n", WSAGetLastError());
            goto cleanup;
        }

        /* Obtain the WSARecvMsg function */
        WSAIoctl(s1, SIO_GET_EXTENSION_FUNCTION_POINTER, &WSARecvMsg_GUID, sizeof(WSARecvMsg_GUID),
                 &pWSARecvMsg, sizeof(pWSARecvMsg), &dwBytes, NULL, NULL);
        if (!pWSARecvMsg)
        {
            win_skip("WSARecvMsg is unsupported, some tests will be skipped.\n");
            closesocket(s1);
            goto cleanup;
        }

        /* Setup the server side socket */
        rc=bind(s1, (struct sockaddr*)&s1addr, sizeof(s1addr));
        ok(rc != SOCKET_ERROR, "bind() failed error: %d\n", WSAGetLastError());
        rc=setsockopt(s1, IPPROTO_IP, IP_PKTINFO, (const char*)&yes, sizeof(yes));
        ok(rc == 0, "failed to set IPPROTO_IP flag IP_PKTINFO!\n");

        /* Build "client" side socket */
        addrlen = sizeof(s2addr);
        if (getsockname(s1, (struct sockaddr *) &s2addr, &addrlen) != 0)
        {
            skip("Failed to call getsockname, some tests skipped: %d\n", WSAGetLastError());
            closesocket(s1);
            goto cleanup;
        }
        s2addr.sin_addr.s_addr = addresses[0]; /* Always target the local adapter address */
        s2=socket(AF_INET, SOCK_DGRAM, 0);
        if (s2 == INVALID_SOCKET)
        {
            skip("socket() failed error, some tests skipped: %d\n", WSAGetLastError());
            closesocket(s1);
            goto cleanup;
        }

        /* Test an empty message header */
        rc=pWSARecvMsg(s1, NULL, NULL, NULL, NULL);
        err=WSAGetLastError();
        ok(rc == SOCKET_ERROR && err == WSAEFAULT, "WSARecvMsg() failed error: %d (ret = %d)\n", err, rc);

        /*
         * Send a packet from the client to the server and test for specifying
         * a short control header.
         */
        SetLastError(0xdeadbeef);
        rc=sendto(s2, msg, sizeof(msg), 0, (struct sockaddr*)&s2addr, sizeof(s2addr));
        ok(rc == sizeof(msg), "sendto() failed error: %d\n", WSAGetLastError());
        ok(GetLastError() == ERROR_SUCCESS, "Expected 0, got %d\n", GetLastError());
        hdr.Control.len = 1;
        rc=pWSARecvMsg(s1, &hdr, &dwSize, NULL, NULL);
        err=WSAGetLastError();
        ok(rc == SOCKET_ERROR && err == WSAEMSGSIZE && (hdr.dwFlags & MSG_CTRUNC),
           "WSARecvMsg() failed error: %d (ret: %d, flags: %d)\n", err, rc, hdr.dwFlags);
        hdr.dwFlags = 0; /* Reset flags */

        /* Perform another short control header test, this time with an overlapped receive */
        hdr.Control.len = 1;
        rc=pWSARecvMsg(s1, &hdr, NULL, &ov, NULL);
        err=WSAGetLastError();
        ok(rc != 0 && err == WSA_IO_PENDING, "WSARecvMsg() failed error: %d\n", err);
        SetLastError(0xdeadbeef);
        rc=sendto(s2, msg, sizeof(msg), 0, (struct sockaddr*)&s2addr, sizeof(s2addr));
        ok(rc == sizeof(msg), "sendto() failed error: %d\n", WSAGetLastError());
        ok(GetLastError() == ERROR_SUCCESS, "Expected 0, got %d\n", GetLastError());
        if (WaitForSingleObject(ov.hEvent, 100) != WAIT_OBJECT_0)
        {
            skip("Server side did not receive packet, some tests skipped.\n");
            closesocket(s2);
            closesocket(s1);
            continue;
        }
        dwFlags = 0;
        WSAGetOverlappedResult(s1, &ov, NULL, FALSE, &dwFlags);
        ok(dwFlags == 0,
           "WSAGetOverlappedResult() returned unexpected flags %d!\n", dwFlags);
        ok(hdr.dwFlags == MSG_CTRUNC,
           "WSARecvMsg() overlapped operation set unexpected flags %d.\n", hdr.dwFlags);
        hdr.dwFlags = 0; /* Reset flags */

        /*
         * Setup an overlapped receive, send a packet, then wait for the packet to be retrieved
         * on the server end and check that the returned packet matches what was sent.
         */
        hdr.Control.len = sizeof(pktbuf);
        rc=pWSARecvMsg(s1, &hdr, NULL, &ov, NULL);
        err=WSAGetLastError();
        ok(rc != 0 && err == WSA_IO_PENDING, "WSARecvMsg() failed error: %d\n", err);
        ok(hdr.Control.len == sizeof(pktbuf),
           "WSARecvMsg() control length mismatch (%d != sizeof pktbuf).\n", hdr.Control.len);
        rc=sendto(s2, msg, sizeof(msg), 0, (struct sockaddr*)&s2addr, sizeof(s2addr));
        ok(rc == sizeof(msg), "sendto() failed error: %d\n", WSAGetLastError());
        if (WaitForSingleObject(ov.hEvent, 100) != WAIT_OBJECT_0)
        {
            skip("Server side did not receive packet, some tests skipped.\n");
            closesocket(s2);
            closesocket(s1);
            continue;
        }
        dwSize = 0;
        WSAGetOverlappedResult(s1, &ov, &dwSize, FALSE, NULL);
        ok(dwSize == sizeof(msg),
           "WSARecvMsg() buffer length does not match transmitted data!\n");
        ok(strncmp(iovec[0].buf, msg, sizeof(msg)) == 0,
           "WSARecvMsg() buffer does not match transmitted data!\n");
        ok(hdr.Control.len == IP_PKTINFO_LEN,
           "WSARecvMsg() control length mismatch (%d).\n", hdr.Control.len);

        /* Test for the expected IP_PKTINFO return information. */
        foundhdr = FALSE;
        for (cmsg = WSA_CMSG_FIRSTHDR(&hdr); cmsg != NULL; cmsg = WSA_CMSG_NXTHDR(&hdr, cmsg))
        {
            if (cmsg->cmsg_level == IPPROTO_IP && cmsg->cmsg_type == IP_PKTINFO)
            {
                struct in_pktinfo *pi = (struct in_pktinfo *)WSA_CMSG_DATA(cmsg);

                ok(pi->ipi_addr.s_addr == s2addr.sin_addr.s_addr, "destination ip mismatch!\n");
                foundhdr = TRUE;
            }
        }
        ok(foundhdr, "IP_PKTINFO header information was not returned!\n");

        closesocket(s2);
        closesocket(s1);
    }

cleanup:
    CloseHandle(ov.hEvent);
}