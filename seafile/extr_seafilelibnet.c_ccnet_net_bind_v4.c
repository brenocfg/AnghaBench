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
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  on ;
typedef  scalar_t__ evutil_socket_t ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 scalar_t__ bind (scalar_t__,struct sockaddr*,int) ; 
 int /*<<< orphan*/  ccnet_warning (char*,char const*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ getsockname (scalar_t__,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  htons (int) ; 
 scalar_t__ inet_aton (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ setsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int sock_port (struct sockaddr*) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char const* strerror (int /*<<< orphan*/ ) ; 

evutil_socket_t
ccnet_net_bind_v4 (const char *ipaddr, int *port)
{
    evutil_socket_t sockfd;
    struct sockaddr_in addr;
    int on = 1;
        
    sockfd = socket (AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        ccnet_warning("create socket failed: %s\n", strerror(errno));
        exit(-1);
    }

    memset (&addr, 0, sizeof (struct sockaddr_in));
    addr.sin_family = AF_INET;
    if (inet_aton(ipaddr, &addr.sin_addr) == 0) {
        ccnet_warning ("Bad ip address %s\n", ipaddr);
        return -1;
    }
    addr.sin_port = htons (*port);

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)) < 0)
    {
        ccnet_warning ("setsockopt of SO_REUSEADDR error: %s\n",
                       strerror(errno));
        return -1;
    }

    if ( bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        ccnet_warning ("Bind error: %s\n", strerror (errno));
        return -1;
    }


    if (*port == 0) {
        struct sockaddr_storage ss;
        socklen_t len;

        len = sizeof(ss);
        if (getsockname(sockfd, (struct sockaddr *)&ss, &len) < 0) {
            ccnet_warning ("getsockname error: %s\n", strerror(errno));
            return -1;
        }
        *port = sock_port ((struct sockaddr *)&ss);
    }

    return sockfd;
}