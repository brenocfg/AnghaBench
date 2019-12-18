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
typedef  int /*<<< orphan*/  hlim ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 int IPV6_MULTICAST_HOPS ; 
 int IP_MULTICAST_TTL ; 
 int SOL_IP ; 
 int SOL_IPV6 ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_errno ; 
 scalar_t__ setsockopt (int,int,int,...) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int net_SetMcastHopLimit( vlc_object_t *p_this,
                                 int fd, int family, int hlim )
{
    int proto, cmd;

    /* There is some confusion in the world whether IP_MULTICAST_TTL
     * takes a byte or an int as an argument.
     * BSD seems to indicate byte so we are going with that and use
     * int as a fallback to be safe */
    switch( family )
    {
#ifdef IP_MULTICAST_TTL
        case AF_INET:
            proto = SOL_IP;
            cmd = IP_MULTICAST_TTL;
            break;
#endif

#ifdef IPV6_MULTICAST_HOPS
        case AF_INET6:
            proto = SOL_IPV6;
            cmd = IPV6_MULTICAST_HOPS;
            break;
#endif

        default:
            errno = EAFNOSUPPORT;
            msg_Warn( p_this, "%s", vlc_strerror_c(EAFNOSUPPORT) );
            return VLC_EGENERIC;
    }

    if( setsockopt( fd, proto, cmd, &hlim, sizeof( hlim ) ) < 0 )
    {
        /* BSD compatibility */
        unsigned char buf;

        msg_Dbg( p_this, "cannot set hop limit (%d): %s", hlim,
                 vlc_strerror_c(net_errno) );
        buf = (unsigned char)(( hlim > 255 ) ? 255 : hlim);
        if( setsockopt( fd, proto, cmd, &buf, sizeof( buf ) ) )
        {
            msg_Err( p_this, "cannot set hop limit (%d): %s", hlim,
                     vlc_strerror_c(net_errno) );
            return VLC_EGENERIC;
        }
    }

    return VLC_SUCCESS;
}