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
struct TYPE_4__ {void* s_addr; } ;
struct sockaddr_in {scalar_t__ sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  selfAddr ;
struct TYPE_5__ {int /*<<< orphan*/  wVersion; } ;
typedef  TYPE_2__ WSADATA ;
typedef  int /*<<< orphan*/  WORD ;
typedef  scalar_t__ SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  DBG (char*) ; 
 int HIBYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 scalar_t__ INVALID_SOCKET ; 
 int LOBYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 scalar_t__ SOCKET_ERROR ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  WSACleanup () ; 
 int WSAStartup (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ accept (scalar_t__,struct sockaddr*,int*) ; 
 scalar_t__ bind (scalar_t__,struct sockaddr*,int) ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 scalar_t__ connect (scalar_t__,struct sockaddr*,int) ; 
 scalar_t__ getsockname (scalar_t__,struct sockaddr*,int*) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ listen (scalar_t__,int) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int SocketTest()
{
   /*
    * A socket pair is often used for interprocess communication,
    * so we need to make sure neither socket is associated with
    * the I/O completion port; otherwise it can't be used by a
    * child process.
    *
    * The default implementation below cannot be used for NT
    * because PR_Accept would have associated the I/O completion
    * port with the listening and accepted sockets.
    */
   SOCKET listenSock;
   SOCKET osfd[2];
   struct sockaddr_in selfAddr, peerAddr;
   int addrLen;
   WORD wVersionRequested;
   WSADATA wsaData;
   int err;

   /*
    * Initialization.
    */

   wVersionRequested = MAKEWORD( 2, 2 );

   DBG("Calling WSAStartup\n");
   err = WSAStartup( wVersionRequested, &wsaData );
   if ( err != 0 ) {
       /* Tell the user that we could not find a usable */
       /* WinSock DLL.                                  */
       DBG("WSAStartup failed\n");
       return 1;
   }

   /* Confirm that the WinSock DLL supports 2.2.*/
   /* Note that if the DLL supports versions greater    */
   /* than 2.2 in addition to 2.2, it will still return */
   /* 2.2 in wVersion since that is the version we      */
   /* requested.                                        */

   if ( LOBYTE( wsaData.wVersion ) != 2 ||
           HIBYTE( wsaData.wVersion ) != 2 ) {
       /* Tell the user that we could not find a usable */
       /* WinSock DLL.                                  */
       DBG("WSAStartup version unacceptable\n");
       WSACleanup( );
       return 1;
   }

   /* The WinSock DLL is acceptable. Proceed. */

   DBG("Calling socket\n");
   osfd[0] = osfd[1] = INVALID_SOCKET;
   listenSock = socket(AF_INET, SOCK_STREAM, 0);
   if (listenSock == INVALID_SOCKET) {
       DBG("socket failed\n");
       goto failed;
   }

   selfAddr.sin_family = AF_INET;
   selfAddr.sin_port = 0;
   selfAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); /* BugZilla: 35408 */
   addrLen = sizeof(selfAddr);
   DBG("Calling bind\n");
   if (bind(listenSock, (struct sockaddr *) &selfAddr,
           addrLen) == SOCKET_ERROR) {
       DBG("bind failed\n");
       goto failed;
   }

   DBG("Calling getsockname\n");
   if (getsockname(listenSock, (struct sockaddr *) &selfAddr,
           &addrLen) == SOCKET_ERROR) {
       DBG("getsockname failed\n");
       goto failed;
   }

   DBG("Calling listen\n");
   if (listen(listenSock, 5) == SOCKET_ERROR) {
       DBG("listen failed\n");
       goto failed;
   }

   DBG("Calling socket\n");
   osfd[0] = socket(AF_INET, SOCK_STREAM, 0);
   if (osfd[0] == INVALID_SOCKET) {
       DBG("socket failed\n");
       goto failed;
   }
   selfAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

   /*
    * Only a thread is used to do the connect and accept.
    * I am relying on the fact that connect returns
    * successfully as soon as the connect request is put
    * into the listen queue (but before accept is called).
    * This is the behavior of the BSD socket code.  If
    * connect does not return until accept is called, we
    * will need to create another thread to call connect.
    */
   DBG("Calling connect\n");
   if (connect(osfd[0], (struct sockaddr *) &selfAddr,
           addrLen) == SOCKET_ERROR) {
       DBG("connect failed\n");
       goto failed;
   }

   /*
    * A malicious local process may connect to the listening
    * socket, so we need to verify that the accepted connection
    * is made from our own socket osfd[0].
    */
   DBG("Calling getsockname\n");
   if (getsockname(osfd[0], (struct sockaddr *) &selfAddr,
           &addrLen) == SOCKET_ERROR) {
       DBG("getsockname failed\n");
       goto failed;
   }

   DBG("Calling accept\n");
   osfd[1] = accept(listenSock, (struct sockaddr *) &peerAddr, &addrLen);
   if (osfd[1] == INVALID_SOCKET) {
       DBG("accept failed\n");
       goto failed;
   }
   if (peerAddr.sin_port != selfAddr.sin_port) {
       /* the connection we accepted is not from osfd[0] */
       DBG("peerAddr.sin_port != selfAddr.sin_port\n");
       goto failed;
   }

   DBG("Hurray!\n");

   closesocket(listenSock);

   closesocket(osfd[0]);
   closesocket(osfd[1]);

   WSACleanup();

   return 0;

failed:
   if (listenSock != INVALID_SOCKET) {
       closesocket(listenSock);
   }
   if (osfd[0] != INVALID_SOCKET) {
       closesocket(osfd[0]);
   }
   if (osfd[1] != INVALID_SOCKET) {
       closesocket(osfd[1]);
   }

   WSACleanup();

   return 1;
}