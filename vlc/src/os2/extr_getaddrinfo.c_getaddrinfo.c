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
typedef  scalar_t__ u_short ;
typedef  int /*<<< orphan*/  u_long ;
struct hostent {int h_length; scalar_t__ h_addrtype; char* h_name; scalar_t__ h_addr; } ;
struct addrinfo {int ai_flags; scalar_t__ ai_family; int ai_socktype; int ai_protocol; struct addrinfo* ai_next; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int AI_CANONNAME ; 
 int AI_NUMERICHOST ; 
 int AI_PASSIVE ; 
 int EAI_BADFLAGS ; 
 int EAI_FAMILY ; 
 int EAI_SERVICE ; 
 int EAI_SOCKTYPE ; 
 int EAI_SYSTEM ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int /*<<< orphan*/  INADDR_NONE ; 
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
#define  SOCK_DGRAM 130 
#define  SOCK_RAW 129 
#define  SOCK_STREAM 128 
 int _AI_MASK ; 
 int /*<<< orphan*/  errno ; 
 int gai_error_from_herrno () ; 
 struct hostent* gethostbyname (char const*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ htons (scalar_t__) ; 
 int /*<<< orphan*/  inet_addr (char const*) ; 
 struct addrinfo* makeipv4info (int const,int,int /*<<< orphan*/ ,scalar_t__,char const*) ; 
 unsigned long strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

int
getaddrinfo (const char *node, const char *service,
             const struct addrinfo *hints, struct addrinfo **res)
{
    struct addrinfo *info;
    u_long ip;
    u_short port;
    int protocol = 0, flags = 0;
    const char *name = NULL;

    if (hints != NULL)
    {
        flags = hints->ai_flags;

        if (flags & ~_AI_MASK)
            return EAI_BADFLAGS;
        /* only accept AF_INET and AF_UNSPEC */
        if (hints->ai_family && (hints->ai_family != AF_INET))
            return EAI_FAMILY;

        /* protocol sanity check */
        switch (hints->ai_socktype)
        {
            case SOCK_STREAM:
                protocol = IPPROTO_TCP;
                break;

            case SOCK_DGRAM:
                protocol = IPPROTO_UDP;
                break;

#ifdef SOCK_RAW
            case SOCK_RAW:
#endif
            case 0:
                break;

            default:
                return EAI_SOCKTYPE;
        }
        if (hints->ai_protocol && protocol
         && (protocol != hints->ai_protocol))
            return EAI_SERVICE;
    }

    *res = NULL;

    /* default values */
    if (node == NULL)
    {
        if (flags & AI_PASSIVE)
            ip = htonl (INADDR_ANY);
        else
            ip = htonl (INADDR_LOOPBACK);
    }
    else
    if ((ip = inet_addr (node)) == INADDR_NONE)
    {
        struct hostent *entry = NULL;

        /* hostname resolution */
        if (!(flags & AI_NUMERICHOST))
            entry = gethostbyname (node);

        if (entry == NULL)
            return gai_error_from_herrno ();

        if ((entry->h_length != 4) || (entry->h_addrtype != AF_INET))
            return EAI_FAMILY;

        ip = *((u_long *) entry->h_addr);
        if (flags & AI_CANONNAME)
            name = entry->h_name;
    }

    if ((flags & AI_CANONNAME) && (name == NULL))
        name = node;

    /* service resolution */
    if (service == NULL)
        port = 0;
    else
    {
        unsigned long d;
        char *end;

        d = strtoul (service, &end, 0);
        if (end[0] || (d > 65535u))
            return EAI_SERVICE;

        port = htons ((u_short)d);
    }

    /* building results... */
    if ((!protocol) || (protocol == IPPROTO_UDP))
    {
        info = makeipv4info (SOCK_DGRAM, IPPROTO_UDP, ip, port, name);
        if (info == NULL)
        {
            errno = ENOMEM;
            return EAI_SYSTEM;
        }
        if (flags & AI_PASSIVE)
            info->ai_flags |= AI_PASSIVE;
        *res = info;
    }
    if ((!protocol) || (protocol == IPPROTO_TCP))
    {
        info = makeipv4info (SOCK_STREAM, IPPROTO_TCP, ip, port, name);
        if (info == NULL)
        {
            errno = ENOMEM;
            return EAI_SYSTEM;
        }
        info->ai_next = *res;
        if (flags & AI_PASSIVE)
            info->ai_flags |= AI_PASSIVE;
        *res = info;
    }

    return 0;
}