#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* ops; } ;
typedef  TYPE_2__ vlc_tls_t ;
struct iovec {void* iov_base; size_t iov_len; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  TYPE_2__* gnutls_transport_ptr_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* readv ) (TYPE_2__*,struct iovec*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct iovec*,int) ; 

__attribute__((used)) static ssize_t vlc_gnutls_read(gnutls_transport_ptr_t ptr, void *buf,
                               size_t length)
{
    vlc_tls_t *sock = ptr;
    struct iovec iov = {
        .iov_base = buf,
        .iov_len = length,
    };

    return sock->ops->readv(sock, &iov, 1);
}