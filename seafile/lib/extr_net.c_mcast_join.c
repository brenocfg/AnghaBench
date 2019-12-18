#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct sockaddr {int sa_family; } ;
struct sockaddr_in6 {struct sockaddr const sin6_addr; } ;
struct sockaddr_in {struct sockaddr const sin_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_3__ {TYPE_2__ s_addr; } ;
struct ipv6_mreq {scalar_t__ gr_interface; scalar_t__ ipv6mr_interface; TYPE_2__ ipv6mr_multiaddr; TYPE_2__ imr_interface; TYPE_1__ imr_multiaddr; TYPE_2__ gr_group; } ;
struct ip_mreq {scalar_t__ gr_interface; scalar_t__ ipv6mr_interface; TYPE_2__ ipv6mr_multiaddr; TYPE_2__ imr_interface; TYPE_1__ imr_multiaddr; TYPE_2__ gr_group; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;
struct ifreq {int /*<<< orphan*/  ifr_addr; int /*<<< orphan*/  ifr_name; } ;
struct group_req {scalar_t__ gr_interface; scalar_t__ ipv6mr_interface; TYPE_2__ ipv6mr_multiaddr; TYPE_2__ imr_interface; TYPE_1__ imr_multiaddr; TYPE_2__ gr_group; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  mreq6 ;
typedef  int /*<<< orphan*/  mreq ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_JOIN_GROUP ; 
 int /*<<< orphan*/  IP_ADD_MEMBERSHIP ; 
 int /*<<< orphan*/  MCAST_JOIN_GROUP ; 
 int /*<<< orphan*/  SIOCGIFADDR ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  family_to_level (int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * if_indextoname (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ if_nametoindex (char const*) ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,struct sockaddr const*,int) ; 
 int setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ipv6_mreq*,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mcast_join(evutil_socket_t sockfd, const struct sockaddr *grp, socklen_t grplen,
		   const char *ifname, u_int ifindex)
{
#if (defined MCAST_JOIN_GROUP) && (! defined __APPLE__)
	struct group_req req;
	if (ifindex > 0) {
		req.gr_interface = ifindex;
	} else if (ifname != NULL) {
		if ( (req.gr_interface = if_nametoindex(ifname)) == 0) {
			errno = ENXIO;	/* i/f name not found */
			return(-1);
		}
	} else
		req.gr_interface = 0;
	if (grplen > sizeof(req.gr_group)) {
		errno = EINVAL;
		return -1;
	}
	memcpy(&req.gr_group, grp, grplen);
	return (setsockopt(sockfd, family_to_level(grp->sa_family),
			MCAST_JOIN_GROUP, &req, sizeof(req)));
#else
/* end mcast_join1 */

/* include mcast_join2 */
	switch (grp->sa_family) {
	case AF_INET: {
		struct ip_mreq		mreq;
		struct ifreq		ifreq;

		memcpy(&mreq.imr_multiaddr.s_addr,
			   &((const struct sockaddr_in *) grp)->sin_addr,
			   sizeof(struct in_addr));

		if (ifindex > 0) {
			if (if_indextoname(ifindex, ifreq.ifr_name) == NULL) {
				errno = ENXIO;	/* i/f index not found */
				return(-1);
			}
			goto doioctl;
		} else if (ifname != NULL) {
			strncpy(ifreq.ifr_name, ifname, IFNAMSIZ);
doioctl:
			if (ioctl(sockfd, SIOCGIFADDR, &ifreq) < 0)
				return(-1);
			memcpy(&mreq.imr_interface,
				   &((struct sockaddr_in *) &ifreq.ifr_addr)->sin_addr,
				   sizeof(struct in_addr));
		} else
			mreq.imr_interface.s_addr = htonl(INADDR_ANY);

		return(setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP,
						  &mreq, sizeof(mreq)));
	}
/* end mcast_join2 */

/* include mcast_join3 */
#ifdef	IPV6
#ifndef	IPV6_JOIN_GROUP		/* APIv0 compatibility */
#define	IPV6_JOIN_GROUP		IPV6_ADD_MEMBERSHIP
#endif
	case AF_INET6: {
		struct ipv6_mreq	mreq6;

		memcpy(&mreq6.ipv6mr_multiaddr,
			   &((const struct sockaddr_in6 *) grp)->sin6_addr,
			   sizeof(struct in6_addr));

		if (ifindex > 0) {
			mreq6.ipv6mr_interface = ifindex;
		} else if (ifname != NULL) {
			if ( (mreq6.ipv6mr_interface = if_nametoindex(ifname)) == 0) {
				errno = ENXIO;	/* i/f name not found */
				return(-1);
			}
		} else
			mreq6.ipv6mr_interface = 0;

		return(setsockopt(sockfd, IPPROTO_IPV6, IPV6_JOIN_GROUP,
						  &mreq6, sizeof(mreq6)));
	}
#endif

	default:
		errno = EAFNOSUPPORT;
		return(-1);
	}
#endif

    return -1;
}