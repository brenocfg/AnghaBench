#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int socklen_t ;
typedef  int ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_9__ {scalar_t__ log_socket_errors; } ;
typedef  TYPE_1__ ngx_http_lua_loc_conf_t ;
struct TYPE_10__ {int kq_errno; scalar_t__ pending_eof; } ;
typedef  TYPE_2__ ngx_event_t ;
struct TYPE_11__ {int /*<<< orphan*/  fd; TYPE_2__* read; TYPE_2__* write; } ;
typedef  TYPE_3__ ngx_connection_t ;

/* Variables and functions */
 int NGX_OK ; 
 int NGX_USE_KQUEUE_EVENT ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ERROR ; 
 int /*<<< orphan*/  dd (char*,TYPE_2__*,scalar_t__,TYPE_2__*,scalar_t__) ; 
 int getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int*) ; 
 int /*<<< orphan*/  ngx_connection_error (TYPE_3__*,int,char*) ; 
 int ngx_errno ; 
 int ngx_event_flags ; 
 TYPE_1__* ngx_http_get_module_loc_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_socket_test_connect(ngx_http_request_t *r, ngx_connection_t *c)
{
    int              err;
    socklen_t        len;

    ngx_http_lua_loc_conf_t     *llcf;

#if (NGX_HAVE_KQUEUE)

    ngx_event_t     *ev;

    if (ngx_event_flags & NGX_USE_KQUEUE_EVENT)  {
        dd("pending eof: (%p)%d (%p)%d", c->write, c->write->pending_eof,
           c->read, c->read->pending_eof);

        if (c->write->pending_eof) {
            ev = c->write;

        } else if (c->read->pending_eof) {
            ev = c->read;

        } else {
            ev = NULL;
        }

        if (ev) {
            llcf = ngx_http_get_module_loc_conf(r, ngx_http_lua_module);
            if (llcf->log_socket_errors) {
                (void) ngx_connection_error(c, ev->kq_errno,
                                            "kevent() reported that "
                                            "connect() failed");
            }
            return ev->kq_errno;
        }

    } else
#endif
    {
        err = 0;
        len = sizeof(int);

        /*
         * BSDs and Linux return 0 and set a pending error in err
         * Solaris returns -1 and sets errno
         */

        if (getsockopt(c->fd, SOL_SOCKET, SO_ERROR, (void *) &err, &len)
            == -1)
        {
            err = ngx_errno;
        }

        if (err) {
            llcf = ngx_http_get_module_loc_conf(r, ngx_http_lua_module);
            if (llcf->log_socket_errors) {
                (void) ngx_connection_error(c, err, "connect() failed");
            }
            return err;
        }
    }

    return NGX_OK;
}