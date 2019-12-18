#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* ops; } ;
typedef  TYPE_2__ vlc_tls_t ;
struct iovec {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;
typedef  int ssize_t ;
typedef  TYPE_2__* gnutls_transport_ptr_t ;
struct TYPE_10__ {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;
typedef  TYPE_4__ giovec_t ;
struct TYPE_8__ {int (* writev ) (TYPE_2__*,struct iovec*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 long IOV_MAX ; 
 int /*<<< orphan*/  _SC_IOV_MAX ; 
 int /*<<< orphan*/  errno ; 
 int stub1 (TYPE_2__*,struct iovec*,int) ; 
 long sysconf (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static ssize_t vlc_gnutls_writev(gnutls_transport_ptr_t ptr,
                                 const giovec_t *giov, int iovcnt)
{
#ifdef IOV_MAX
    const long iovmax = IOV_MAX;
#else
    const long iovmax = sysconf(_SC_IOV_MAX);
#endif
    if (unlikely(iovcnt > iovmax))
    {
        errno = EINVAL;
        return -1;
    }
    if (unlikely(iovcnt == 0))
        return 0;

    vlc_tls_t *sock = ptr;
    struct iovec iov[iovcnt];

    for (int i = 0; i < iovcnt; i++)
    {
        iov[i].iov_base = giov[i].iov_base;
        iov[i].iov_len = giov[i].iov_len;
    }

    return sock->ops->writev(sock, iov, iovcnt);
}