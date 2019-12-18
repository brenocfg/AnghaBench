#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct addrinfo {int ai_family; int ai_addrlen; scalar_t__ ai_addr; struct addrinfo* ai_next; int /*<<< orphan*/  ai_socktype; } ;
typedef  scalar_t__ sa_family_t ;
typedef  int /*<<< orphan*/  hints ;
struct TYPE_10__ {int /*<<< orphan*/  in6_addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  in_addr; } ;
struct TYPE_11__ {scalar_t__ family; TYPE_2__ ip6; TYPE_1__ ip4; } ;
typedef  TYPE_3__ IP ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 scalar_t__ AF_UNSPEC ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int TOX_ADDR_RESOLVE_INET ; 
 int TOX_ADDR_RESOLVE_INET6 ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int getaddrinfo (char const*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  ip_copy (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ip_init (TYPE_3__*,int) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ networking_at_startup () ; 

int addr_resolve(const char *address, IP *to, IP *extra)
{
    if (!address || !to)
        return 0;

    sa_family_t family = to->family;

    struct addrinfo *server = NULL;
    struct addrinfo *walker = NULL;
    struct addrinfo  hints;
    int rc;
    int result = 0;
    int done = 0;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = family;
    hints.ai_socktype = SOCK_DGRAM; // type of socket Tox uses.

    if (networking_at_startup() != 0)
        return 0;

    rc = getaddrinfo(address, NULL, &hints, &server);

    // Lookup failed.
    if (rc != 0) {
        return 0;
    }

    IP ip4;
    ip_init(&ip4, 0); // ipv6enabled = 0
    IP ip6;
    ip_init(&ip6, 1); // ipv6enabled = 1

    for (walker = server; (walker != NULL) && !done; walker = walker->ai_next) {
        switch (walker->ai_family) {
            case AF_INET:
                if (walker->ai_family == family) { /* AF_INET requested, done */
                    struct sockaddr_in *addr = (struct sockaddr_in *)walker->ai_addr;
                    to->ip4.in_addr = addr->sin_addr;
                    result = TOX_ADDR_RESOLVE_INET;
                    done = 1;
                } else if (!(result & TOX_ADDR_RESOLVE_INET)) { /* AF_UNSPEC requested, store away */
                    struct sockaddr_in *addr = (struct sockaddr_in *)walker->ai_addr;
                    ip4.ip4.in_addr = addr->sin_addr;
                    result |= TOX_ADDR_RESOLVE_INET;
                }

                break; /* switch */

            case AF_INET6:
                if (walker->ai_family == family) { /* AF_INET6 requested, done */
                    if (walker->ai_addrlen == sizeof(struct sockaddr_in6)) {
                        struct sockaddr_in6 *addr = (struct sockaddr_in6 *)walker->ai_addr;
                        to->ip6.in6_addr = addr->sin6_addr;
                        result = TOX_ADDR_RESOLVE_INET6;
                        done = 1;
                    }
                } else if (!(result & TOX_ADDR_RESOLVE_INET6)) { /* AF_UNSPEC requested, store away */
                    if (walker->ai_addrlen == sizeof(struct sockaddr_in6)) {
                        struct sockaddr_in6 *addr = (struct sockaddr_in6 *)walker->ai_addr;
                        ip6.ip6.in6_addr = addr->sin6_addr;
                        result |= TOX_ADDR_RESOLVE_INET6;
                    }
                }

                break; /* switch */
        }
    }

    if (family == AF_UNSPEC) {
        if (result & TOX_ADDR_RESOLVE_INET6) {
            ip_copy(to, &ip6);

            if ((result & TOX_ADDR_RESOLVE_INET) && (extra != NULL)) {
                ip_copy(extra, &ip4);
            }
        } else if (result & TOX_ADDR_RESOLVE_INET) {
            ip_copy(to, &ip4);
        } else {
            result = 0;
        }
    }

    freeaddrinfo(server);
    return result;
}