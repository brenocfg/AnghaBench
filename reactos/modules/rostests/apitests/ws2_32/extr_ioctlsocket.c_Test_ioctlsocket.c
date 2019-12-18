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
typedef  int /*<<< orphan*/  WSADATA ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  SOCKET ;
typedef  scalar_t__ LPSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ConnectToReactOSWebsite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateSocket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FIONREAD ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetRequestAndWait (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  SCKTEST (int) ; 
 int SOCKET_ERROR ; 
 int /*<<< orphan*/  WSACleanup () ; 
 int WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  closesocket (int /*<<< orphan*/ ) ; 
 int ioctlsocket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int recv (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 

int Test_ioctlsocket()
{
    LPSTR pszBuf;
    int iResult;
    SOCKET sck;
    ULONG BytesAvailable;
    ULONG BytesToRead;
    WSADATA wdata;

    /* Start up Winsock */
    iResult = WSAStartup(MAKEWORD(2, 2), &wdata);
    ok(iResult == 0, "WSAStartup failed. iResult = %d\n", iResult);

    /* If we call ioctlsocket without a socket, it should return with an error and do nothing. */
    BytesAvailable = 0xdeadbeef;
    iResult = ioctlsocket(0, FIONREAD, &BytesAvailable);
    ok(iResult == SOCKET_ERROR, "iResult = %d\n", iResult);
    ok(BytesAvailable == 0xdeadbeef, "BytesAvailable = %ld\n", BytesAvailable);

    /* Create the socket */
    if (!CreateSocket(&sck))
    {
        ok(0, "CreateSocket failed. Aborting test.\n");
        return 0;
    }

    /* Now we can pass at least a socket, but we have no connection yet. The function should return 0. */
    BytesAvailable = 0xdeadbeef;
    iResult = ioctlsocket(sck, FIONREAD, &BytesAvailable);
    ok(iResult == 0, "iResult = %d\n", iResult);
    ok(BytesAvailable == 0, "BytesAvailable = %ld\n", BytesAvailable);

    /* Connect to "www.reactos.org" */
    if (!ConnectToReactOSWebsite(sck))
    {
        ok(0, "ConnectToReactOSWebsite failed. Aborting test.\n");
        return 0;
    }

    /* Even with a connection, there shouldn't be any bytes available. */
    iResult = ioctlsocket(sck, FIONREAD, &BytesAvailable);
    ok(iResult == 0, "iResult = %d\n", iResult);
    ok(BytesAvailable == 0, "BytesAvailable = %ld\n", BytesAvailable);

    /* Send the GET request */
    if (!GetRequestAndWait(sck))
    {
        ok(0, "GetRequestAndWait failed. Aborting test.\n");
        return 0;
    }

    /* Try ioctlsocket with FIONREAD. There should be bytes available now. */
    SCKTEST(ioctlsocket(sck, FIONREAD, &BytesAvailable));
    ok(BytesAvailable != 0, "BytesAvailable = %ld\n", BytesAvailable);

    /* Get half of the data */
    BytesToRead = BytesAvailable / 2;
    pszBuf = (LPSTR) HeapAlloc(GetProcessHeap(), 0, BytesToRead);
    SCKTEST(recv(sck, pszBuf, BytesToRead, 0));
    HeapFree(GetProcessHeap(), 0, pszBuf);

    BytesToRead = BytesAvailable - BytesToRead;

    /* Now try ioctlsocket again. BytesAvailable should be at the value saved in BytesToRead now. */
    SCKTEST(ioctlsocket(sck, FIONREAD, &BytesAvailable));
    ok(BytesAvailable == BytesToRead, "BytesAvailable = %ld\n", BytesAvailable);

    /* Read those bytes */
    pszBuf = (LPSTR) HeapAlloc(GetProcessHeap(), 0, BytesToRead);
    SCKTEST(recv(sck, pszBuf, BytesToRead, 0));
    HeapFree(GetProcessHeap(), 0, pszBuf);

    /* Try it for the last time. BytesAvailable should be at 0 now. */
    SCKTEST(ioctlsocket(sck, FIONREAD, &BytesAvailable));
    ok(BytesAvailable == 0, "BytesAvailable = %ld\n", BytesAvailable);

    closesocket(sck);
    WSACleanup();
    return 1;
}