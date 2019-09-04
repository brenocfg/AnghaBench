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
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  on ;
typedef  int evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 scalar_t__ bind (int,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccnet_warning (char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct sockaddr*) ; 
 struct sockaddr* malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ mcast_join (int,struct sockaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

evutil_socket_t
create_multicast_sock (struct sockaddr *sasend, socklen_t salen)
{
    int                 ret;
    const int           on = 1;
    evutil_socket_t     recvfd;
    struct sockaddr    *sarecv;

    if ( (recvfd = socket (sasend->sa_family, SOCK_DGRAM, 0)) < 0) {
        ccnet_warning ("Create multicast listen socket fails: %s\n",
                     strerror(errno));
        return -1;
    }
    ret = setsockopt(recvfd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
    if (ret < 0)
        ccnet_warning("Failed to setsockopt SO_REUSEADDR\n");
    sarecv = malloc(salen);
    memcpy(sarecv, sasend, salen);

    if (bind(recvfd, sarecv, salen) < 0) {
        ccnet_warning ("Bind multicast listen socket fails: %s\n",
                       strerror(errno));
        free (sarecv);
        return -1;
    }
    free (sarecv);

    if (mcast_join(recvfd, sasend, salen, NULL, 0) < 0) {
        ccnet_warning ("mcast_join error: %s\n", strerror(errno));
        return -1;
    }

    return recvfd;
}