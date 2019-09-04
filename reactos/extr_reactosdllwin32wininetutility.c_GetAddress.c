#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {void* sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {void* sin_port; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  hints ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {int ai_family; int ai_addrlen; int /*<<< orphan*/  ai_addr; } ;
typedef  int /*<<< orphan*/  INTERNET_PORT ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_1__ ADDRINFOW ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FreeAddrInfoW (TYPE_1__*) ; 
 int GetAddrInfoW (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__**) ; 
 int /*<<< orphan*/  INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_ntop (int,void*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

BOOL GetAddress(const WCHAR *name, INTERNET_PORT port, struct sockaddr *psa, int *sa_len, char *addr_str)
{
    ADDRINFOW *res, hints;
    void *addr = NULL;
    int ret;

    TRACE("%s\n", debugstr_w(name));

    memset( &hints, 0, sizeof(hints) );
    /* Prefer IPv4 to IPv6 addresses, since some servers do not listen on
     * their IPv6 addresses even though they have IPv6 addresses in the DNS.
     */
    hints.ai_family = AF_INET;

    ret = GetAddrInfoW(name, NULL, &hints, &res);
    if (ret != 0)
    {
        TRACE("failed to get IPv4 address of %s, retrying with IPv6\n", debugstr_w(name));
        hints.ai_family = AF_INET6;
        ret = GetAddrInfoW(name, NULL, &hints, &res);
    }
    if (ret != 0)
    {
        TRACE("failed to get address of %s\n", debugstr_w(name));
        return FALSE;
    }
    if (*sa_len < res->ai_addrlen)
    {
        WARN("address too small\n");
        FreeAddrInfoW(res);
        return FALSE;
    }
    *sa_len = res->ai_addrlen;
    memcpy( psa, res->ai_addr, res->ai_addrlen );
    /* Copy port */
    switch (res->ai_family)
    {
    case AF_INET:
        addr = &((struct sockaddr_in *)psa)->sin_addr;
        ((struct sockaddr_in *)psa)->sin_port = htons(port);
        break;
    case AF_INET6:
        addr = &((struct sockaddr_in6 *)psa)->sin6_addr;
        ((struct sockaddr_in6 *)psa)->sin6_port = htons(port);
        break;
    }

    if(addr_str)
        inet_ntop(res->ai_family, addr, addr_str, INET6_ADDRSTRLEN);
    FreeAddrInfoW(res);
    return TRUE;
}