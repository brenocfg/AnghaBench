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
struct TYPE_2__ {scalar_t__ s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct in_addr {scalar_t__ s_addr; } ;
struct hostent {scalar_t__ h_addr; } ;
typedef  int /*<<< orphan*/  WSADATA ;
typedef  scalar_t__ SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ INADDR_NONE ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  R_ERROR ; 
 int /*<<< orphan*/  R_STATUS ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  WSACleanup () ; 
 char const* WSAGetLastError () ; 
 scalar_t__ WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 int /*<<< orphan*/  connect (scalar_t__,struct sockaddr*,int) ; 
 struct hostent* gethostbyname (char const*) ; 
 int /*<<< orphan*/  htons (int) ; 
 scalar_t__ inet_addr (char const*) ; 
 int /*<<< orphan*/  report (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static SOCKET
open_http (const char *server)
{
    WSADATA wsad;
    struct sockaddr_in sa;
    SOCKET s;

    report (R_STATUS, "Opening HTTP connection to %s", server);
    if (WSAStartup (MAKEWORD (2,2), &wsad)) return INVALID_SOCKET;

    sa.sin_family = AF_INET;
    sa.sin_port = htons (80);
    sa.sin_addr.s_addr = inet_addr (server);
    if (sa.sin_addr.s_addr == INADDR_NONE) {
        struct hostent *host = gethostbyname (server);
        if (!host) {
            report (R_ERROR, "Hostname lookup failed for %s", server);
            goto failure;
        }
        sa.sin_addr.s_addr = ((struct in_addr *)host->h_addr)->s_addr;
    }
    s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET) {
        report (R_ERROR, "Can't open network socket: %d",
                WSAGetLastError ());
        goto failure;
    }
    if (!connect (s, (struct sockaddr*)&sa, sizeof (struct sockaddr_in)))
        return s;

    report (R_ERROR, "Can't connect: %d", WSAGetLastError ());
    closesocket (s);
 failure:
    WSACleanup ();
    return INVALID_SOCKET;
}