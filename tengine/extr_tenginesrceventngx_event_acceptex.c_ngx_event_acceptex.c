#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_socket_t ;
struct TYPE_18__ {scalar_t__ len; int /*<<< orphan*/ * data; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* handler ) (TYPE_5__*) ;int /*<<< orphan*/  addr_text_max_len; scalar_t__ addr_ntop; scalar_t__ post_accept_buffer_size; scalar_t__ socklen; int /*<<< orphan*/  fd; TYPE_8__ addr_text; } ;
typedef  TYPE_3__ ngx_listening_t ;
struct TYPE_12__ {int /*<<< orphan*/  error; } ;
struct TYPE_15__ {scalar_t__ available; TYPE_1__ ovlp; TYPE_5__* data; } ;
typedef  TYPE_4__ ngx_event_t ;
struct TYPE_16__ {int /*<<< orphan*/  number; TYPE_8__ addr_text; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; int /*<<< orphan*/  pool; TYPE_2__* buffer; int /*<<< orphan*/  local_socklen; int /*<<< orphan*/  local_sockaddr; TYPE_7__* log; int /*<<< orphan*/  fd; TYPE_3__* listening; } ;
typedef  TYPE_5__ ngx_connection_t ;
struct TYPE_17__ {int /*<<< orphan*/  handler; } ;
struct TYPE_13__ {scalar_t__ start; scalar_t__ end; int /*<<< orphan*/  last; int /*<<< orphan*/  pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_CRIT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_UPDATE_ACCEPT_CONTEXT ; 
 int /*<<< orphan*/  ngx_accept_log_error ; 
 int /*<<< orphan*/  ngx_atomic_fetch_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_connection_counter ; 
 int /*<<< orphan*/  ngx_event_post_acceptex (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ngx_getacceptexsockaddrs (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ,char*,TYPE_8__*) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_sock_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_socket_errno ; 
 int setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 

void
ngx_event_acceptex(ngx_event_t *rev)
{
    ngx_listening_t   *ls;
    ngx_connection_t  *c;

    c = rev->data;
    ls = c->listening;

    c->log->handler = ngx_accept_log_error;

    ngx_log_debug1(NGX_LOG_DEBUG_EVENT, c->log, 0, "AcceptEx: %d", c->fd);

    if (rev->ovlp.error) {
        ngx_log_error(NGX_LOG_CRIT, c->log, rev->ovlp.error,
                      "AcceptEx() %V failed", &ls->addr_text);
        return;
    }

    /* SO_UPDATE_ACCEPT_CONTEXT is required for shutdown() to work */

    if (setsockopt(c->fd, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT,
                   (char *) &ls->fd, sizeof(ngx_socket_t))
        == -1)
    {
        ngx_log_error(NGX_LOG_CRIT, c->log, ngx_socket_errno,
                      "setsockopt(SO_UPDATE_ACCEPT_CONTEXT) failed for %V",
                      &c->addr_text);
        /* TODO: close socket */
        return;
    }

    ngx_getacceptexsockaddrs(c->buffer->pos,
                             ls->post_accept_buffer_size,
                             ls->socklen + 16,
                             ls->socklen + 16,
                             &c->local_sockaddr, &c->local_socklen,
                             &c->sockaddr, &c->socklen);

    if (ls->post_accept_buffer_size) {
        c->buffer->last += rev->available;
        c->buffer->end = c->buffer->start + ls->post_accept_buffer_size;

    } else {
        c->buffer = NULL;
    }

    if (ls->addr_ntop) {
        c->addr_text.data = ngx_pnalloc(c->pool, ls->addr_text_max_len);
        if (c->addr_text.data == NULL) {
            /* TODO: close socket */
            return;
        }

        c->addr_text.len = ngx_sock_ntop(c->sockaddr, c->socklen,
                                         c->addr_text.data,
                                         ls->addr_text_max_len, 0);
        if (c->addr_text.len == 0) {
            /* TODO: close socket */
            return;
        }
    }

    ngx_event_post_acceptex(ls, 1);

    c->number = ngx_atomic_fetch_add(ngx_connection_counter, 1);

    ls->handler(c);

    return;

}