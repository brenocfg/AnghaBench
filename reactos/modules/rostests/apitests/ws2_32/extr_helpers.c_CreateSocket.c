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
typedef  scalar_t__ SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  WSACleanup () ; 
 int WSAGetLastError () ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int CreateSocket(SOCKET* psck)
{
    /* Create the socket */
    *psck = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    ok(*psck != INVALID_SOCKET, "*psck = %d\n", *psck);

    if(*psck == INVALID_SOCKET)
    {
        printf("Winsock error code is %u\n", WSAGetLastError());
        WSACleanup();
        return 0;
    }

    return 1;
}