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
typedef  int /*<<< orphan*/  uint8_t ;
struct iovec {void* iov_base; size_t iov_len; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_8__ {TYPE_2__* sock; } ;
typedef  TYPE_3__ httpd_client_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* writev ) (TYPE_2__*,struct iovec const*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct iovec const*,int) ; 

__attribute__((used)) static
ssize_t httpd_NetSend (httpd_client_t *cl, const uint8_t *p, size_t i_len)
{
    vlc_tls_t *sock = cl->sock;
    const struct iovec iov = { .iov_base = (void *)p, .iov_len = i_len };
    return sock->ops->writev(sock, &iov, 1);
}