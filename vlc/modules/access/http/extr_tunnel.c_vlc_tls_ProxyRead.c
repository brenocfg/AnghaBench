#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* ops; } ;
typedef  TYPE_2__ vlc_tls_t ;
struct TYPE_8__ {TYPE_2__* sock; } ;
typedef  TYPE_3__ vlc_tls_proxy_t ;
struct iovec {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* readv ) (TYPE_2__*,struct iovec*,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct iovec*,unsigned int) ; 

__attribute__((used)) static ssize_t vlc_tls_ProxyRead(vlc_tls_t *tls, struct iovec *iov,
                                 unsigned count)
{
    vlc_tls_proxy_t *proxy = (vlc_tls_proxy_t *)tls;
    vlc_tls_t *sock = proxy->sock;

    return sock->ops->readv(sock, iov, count);
}