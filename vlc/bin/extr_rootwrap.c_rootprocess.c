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
typedef  int /*<<< orphan*/  val ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IPV6_V6ONLY ; 
 int PF_INET ; 
 int PF_INET6 ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 scalar_t__ bind (int,struct sockaddr*,unsigned int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  is_allowed_port (int /*<<< orphan*/ ) ; 
 int recv (int,struct sockaddr_storage*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_err (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_fd (int,int) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const*,int) ; 
 int socket (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rootprocess (int fd)
{
    union
    {
        struct sockaddr         sa;
        struct sockaddr_storage ss;
        struct sockaddr_in      sin;
#ifdef AF_INET6
        struct sockaddr_in6     sin6;
#endif
    } addr;

    while (recv (fd, &addr.ss, sizeof (addr.ss), 0) == sizeof (addr.ss))
    {
        unsigned len;
        int sock;
        int family;

        switch (addr.sa.sa_family)
        {
            case AF_INET:
                if (!is_allowed_port (addr.sin.sin_port))
                {
                    if (send_err (fd, EACCES))
                        return;
                    continue;
                }
                len = sizeof (struct sockaddr_in);
                family = PF_INET;
                break;

#ifdef AF_INET6
            case AF_INET6:
                if (!is_allowed_port (addr.sin6.sin6_port))
                {
                    if (send_err (fd, EACCES))
                        return;
                    continue;
                }
                len = sizeof (struct sockaddr_in6);
                family = PF_INET6;
                break;
#endif

            default:
                if (send_err (fd, EAFNOSUPPORT))
                    return;
                continue;
        }

        sock = socket (family, SOCK_STREAM, IPPROTO_TCP);
        if (sock != -1)
        {
            const int val = 1;

            setsockopt (sock, SOL_SOCKET, SO_REUSEADDR, &val, sizeof (val));
#ifdef AF_INET6
            if (addr.sa.sa_family == AF_INET6)
                setsockopt (sock, IPPROTO_IPV6, IPV6_V6ONLY, &val, sizeof (val));
#endif
            if (bind (sock, &addr.sa, len) == 0)
            {
                send_fd (fd, sock);
                close (sock);
                continue;
            }
            close (sock);
        }
        send_err (fd, errno);
    }
}