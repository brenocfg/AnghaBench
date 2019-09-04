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
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  addr ;
typedef  scalar_t__ SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ accept (scalar_t__,struct sockaddr*,int*) ; 
 int bind (scalar_t__,struct sockaddr*,int) ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 int connect (scalar_t__,struct sockaddr*,int) ; 
 int getsockname (scalar_t__,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  inet_addr (char*) ; 
 int listen (scalar_t__,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcp_socketpair(SOCKET *src, SOCKET *dst)
{
    SOCKET server = INVALID_SOCKET;
    struct sockaddr_in addr;
    int len;
    int ret;

    *src = INVALID_SOCKET;
    *dst = INVALID_SOCKET;

    *src = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (*src == INVALID_SOCKET)
        goto end;

    server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server == INVALID_SOCKET)
        goto end;

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    ret = bind(server, (struct sockaddr*)&addr, sizeof(addr));
    if (ret != 0)
        goto end;

    len = sizeof(addr);
    ret = getsockname(server, (struct sockaddr*)&addr, &len);
    if (ret != 0)
        goto end;

    ret = listen(server, 1);
    if (ret != 0)
        goto end;

    ret = connect(*src, (struct sockaddr*)&addr, sizeof(addr));
    if (ret != 0)
        goto end;

    len = sizeof(addr);
    *dst = accept(server, (struct sockaddr*)&addr, &len);

end:
    if (server != INVALID_SOCKET)
        closesocket(server);
    if (*src != INVALID_SOCKET && *dst != INVALID_SOCKET)
        return 0;
    closesocket(*src);
    closesocket(*dst);
    return -1;
}