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
typedef  int /*<<< orphan*/  netconn_t ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  TRUE ; 

BOOL netconn_is_alive( netconn_t *netconn )
{
#ifdef MSG_DONTWAIT
    ssize_t len;
    BYTE b;

    len = recv( netconn->socket, &b, 1, MSG_PEEK | MSG_DONTWAIT );
    return len == 1 || (len == -1 && errno == EWOULDBLOCK);
#elif defined(__MINGW32__) || defined(_MSC_VER)
    ULONG mode;
    int len;
    char b;

    mode = 1;
    if(!ioctlsocket(netconn->socket, FIONBIO, &mode))
        return FALSE;

    len = recv(netconn->socket, &b, 1, MSG_PEEK);

    mode = 0;
    if(!ioctlsocket(netconn->socket, FIONBIO, &mode))
        return FALSE;

    return len == 1 || (len == -1 && WSAGetLastError() == WSAEWOULDBLOCK);
#else
    FIXME("not supported on this platform\n");
    return TRUE;
#endif
}