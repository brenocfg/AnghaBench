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
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_family; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int INET6_ADDRSTRLEN ; 
 int MAX_CNAME ; 
 int gethostname (char*,int) ; 
 int getsockname (int,struct sockaddr*,int /*<<< orphan*/ *) ; 
 char* inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,...) ; 

__attribute__((used)) static inline void populate_cname(int fd, char *identifier)
{
    /* Set the CNAME Identifier as host@ip:port and fallback to hostname if needed */
    char hostname[MAX_CNAME];
    struct sockaddr_storage peer_sockaddr;
    int name_length = 0;
    socklen_t peer_socklen = 0;
    int ret_hostname = gethostname(hostname, MAX_CNAME);
    if (ret_hostname == -1)
        snprintf(hostname, MAX_CNAME, "UnknownHost");
    int ret_sockname = getsockname(fd, (struct sockaddr *)&peer_sockaddr, &peer_socklen);
    if (ret_sockname == 0)
    {
        struct sockaddr *peer = (struct sockaddr *)&peer_sockaddr;
        if (peer->sa_family == AF_INET) {
            struct sockaddr_in *xin = (void*)peer;
            name_length = snprintf(identifier, MAX_CNAME, "%s@%s:%u", hostname,
                            inet_ntoa(xin->sin_addr), ntohs(xin->sin_port));
            if (name_length >= MAX_CNAME)
                identifier[MAX_CNAME-1] = 0;
        } else if (peer->sa_family == AF_INET6) {
            struct sockaddr_in6 *xin6 = (void*)peer;
            char str[INET6_ADDRSTRLEN];
            inet_ntop(xin6->sin6_family, &xin6->sin6_addr, str, sizeof(struct in6_addr));
            name_length = snprintf(identifier, MAX_CNAME, "%s@%s:%u", hostname,
                            str, ntohs(xin6->sin6_port));
            if (name_length >= MAX_CNAME)
                identifier[MAX_CNAME-1] = 0;
        }
    }
    if (name_length == 0)
    {
        name_length = snprintf(identifier, MAX_CNAME, "%s", hostname);
        if (name_length >= MAX_CNAME)
            identifier[MAX_CNAME-1] = 0;
    }
}