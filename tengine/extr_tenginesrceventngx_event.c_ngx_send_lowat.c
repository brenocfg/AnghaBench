#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_4__ {int sndlowat; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_SNDLOWAT ; 
 int /*<<< orphan*/  ngx_connection_error (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_socket_errno ; 
 int setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int) ; 

ngx_int_t
ngx_send_lowat(ngx_connection_t *c, size_t lowat)
{
    int  sndlowat;

#if (NGX_HAVE_LOWAT_EVENT)

    if (ngx_event_flags & NGX_USE_KQUEUE_EVENT) {
        c->write->available = lowat;
        return NGX_OK;
    }

#endif

    if (lowat == 0 || c->sndlowat) {
        return NGX_OK;
    }

    sndlowat = (int) lowat;

    if (setsockopt(c->fd, SOL_SOCKET, SO_SNDLOWAT,
                   (const void *) &sndlowat, sizeof(int))
        == -1)
    {
        ngx_connection_error(c, ngx_socket_errno,
                             "setsockopt(SO_SNDLOWAT) failed");
        return NGX_ERROR;
    }

    c->sndlowat = 1;

    return NGX_OK;
}