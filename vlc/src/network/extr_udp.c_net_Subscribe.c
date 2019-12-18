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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_scope_id; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int sa_family; } ;
struct ipv6_mreq {int /*<<< orphan*/  imr_multiaddr; int /*<<< orphan*/  ipv6mr_interface; int /*<<< orphan*/  ipv6mr_multiaddr; int /*<<< orphan*/  gr_group; int /*<<< orphan*/  gr_interface; } ;
struct ip_mreq {int /*<<< orphan*/  imr_multiaddr; int /*<<< orphan*/  ipv6mr_interface; int /*<<< orphan*/  ipv6mr_multiaddr; int /*<<< orphan*/  gr_group; int /*<<< orphan*/  gr_interface; } ;
struct group_req {int /*<<< orphan*/  imr_multiaddr; int /*<<< orphan*/  ipv6mr_interface; int /*<<< orphan*/  ipv6mr_multiaddr; int /*<<< orphan*/  gr_group; int /*<<< orphan*/  gr_interface; } ;
typedef  scalar_t__ socklen_t ;
typedef  int /*<<< orphan*/  ipv6mr ;
typedef  int /*<<< orphan*/  imr ;
typedef  int /*<<< orphan*/  gr ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 int /*<<< orphan*/  IPV6_JOIN_GROUP ; 
 int /*<<< orphan*/  IP_ADD_MEMBERSHIP ; 
 int /*<<< orphan*/  MCAST_JOIN_GROUP ; 
 int SOL_IP ; 
 int SOL_IPV6 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr const*,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct ipv6_mreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_errno ; 
 scalar_t__ setsockopt (int,int,int /*<<< orphan*/ ,struct ipv6_mreq*,int) ; 
 int /*<<< orphan*/  var_GetIfIndex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int net_Subscribe(vlc_object_t *obj, int fd,
                         const struct sockaddr *grp, socklen_t grplen)
{
/* MCAST_JOIN_GROUP was introduced to OS X in v10.7, but it doesn't work,
 * so ignore it to use the same code as on 10.5 or 10.6 */
#if defined (MCAST_JOIN_GROUP) && !defined (__APPLE__)
    /* Family-agnostic Any-Source Multicast join */
    int level;
    struct group_req gr;

    memset (&gr, 0, sizeof (gr));
    gr.gr_interface = var_GetIfIndex (obj);

    switch (grp->sa_family)
    {
#ifdef AF_INET6
        case AF_INET6:
        {
            const struct sockaddr_in6 *g6 = (const struct sockaddr_in6 *)grp;

            level = SOL_IPV6;
            assert(grplen >= (socklen_t)sizeof (struct sockaddr_in6));
            if (g6->sin6_scope_id != 0)
                gr.gr_interface = g6->sin6_scope_id;
            break;
        }
#endif
        case AF_INET:
            level = SOL_IP;
            break;
        default:
            errno = EAFNOSUPPORT;
            return -1;
    }

    assert(grplen <= (socklen_t)sizeof (gr.gr_group));
    memcpy (&gr.gr_group, grp, grplen);
    if (setsockopt (fd, level, MCAST_JOIN_GROUP, &gr, sizeof (gr)) == 0)
        return 0;

#else
    switch (grp->sa_family)
    {
# ifdef IPV6_JOIN_GROUP
        case AF_INET6:
        {
            struct ipv6_mreq ipv6mr;
            const struct sockaddr_in6 *g6 = (const struct sockaddr_in6 *)grp;

            memset (&ipv6mr, 0, sizeof (ipv6mr));
            assert(grplen >= (socklen_t)sizeof (struct sockaddr_in6));
            ipv6mr.ipv6mr_multiaddr = g6->sin6_addr;
            ipv6mr.ipv6mr_interface = g6->sin6_scope_id;
            if (!setsockopt (fd, SOL_IPV6, IPV6_JOIN_GROUP,
                             &ipv6mr, sizeof (ipv6mr)))
                return 0;
            break;
        }
# endif
# ifdef IP_ADD_MEMBERSHIP
        case AF_INET:
        {
            struct ip_mreq imr;

            memset (&imr, 0, sizeof (imr));
            assert(grplen >= (socklen_t)sizeof (struct sockaddr_in));
            imr.imr_multiaddr = ((const struct sockaddr_in *)grp)->sin_addr;
            if (setsockopt (fd, SOL_IP, IP_ADD_MEMBERSHIP,
                            &imr, sizeof (imr)) == 0)
                return 0;
            break;
        }
# endif
        default:
            errno = EAFNOSUPPORT;
    }

#endif
    msg_Err (obj, "cannot join multicast group: %s",
             vlc_strerror_c(net_errno));
    return -1;
}