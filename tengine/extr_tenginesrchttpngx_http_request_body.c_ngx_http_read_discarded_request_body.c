#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_11__ {scalar_t__ content_length_n; } ;
struct TYPE_12__ {TYPE_5__* connection; TYPE_2__ headers_in; int /*<<< orphan*/  read_event_handler; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_13__ {int temporary; int /*<<< orphan*/ * last; int /*<<< orphan*/ * pos; } ;
typedef  TYPE_4__ ngx_buf_t ;
struct TYPE_14__ {scalar_t__ (* recv ) (TYPE_5__*,int /*<<< orphan*/ *,size_t) ;int error; TYPE_1__* read; int /*<<< orphan*/  log; } ;
struct TYPE_10__ {int /*<<< orphan*/  ready; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_ERROR ; 
 int NGX_HTTP_DISCARD_BUFFER_SIZE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_http_block_reading ; 
 scalar_t__ ngx_http_discard_request_body_filter (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_4__*,int) ; 
 scalar_t__ ngx_min (scalar_t__,int) ; 
 scalar_t__ stub1 (TYPE_5__*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static ngx_int_t
ngx_http_read_discarded_request_body(ngx_http_request_t *r)
{
    size_t     size;
    ssize_t    n;
    ngx_int_t  rc;
    ngx_buf_t  b;
    u_char     buffer[NGX_HTTP_DISCARD_BUFFER_SIZE];

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http read discarded body");

    ngx_memzero(&b, sizeof(ngx_buf_t));

    b.temporary = 1;

    for ( ;; ) {
        if (r->headers_in.content_length_n == 0) {
            r->read_event_handler = ngx_http_block_reading;
            return NGX_OK;
        }

        if (!r->connection->read->ready) {
            return NGX_AGAIN;
        }

        size = (size_t) ngx_min(r->headers_in.content_length_n,
                                NGX_HTTP_DISCARD_BUFFER_SIZE);

        n = r->connection->recv(r->connection, buffer, size);

        if (n == NGX_ERROR) {
            r->connection->error = 1;
            return NGX_OK;
        }

        if (n == NGX_AGAIN) {
            return NGX_AGAIN;
        }

        if (n == 0) {
            return NGX_OK;
        }

        b.pos = buffer;
        b.last = buffer + n;

        rc = ngx_http_discard_request_body_filter(r, &b);

        if (rc != NGX_OK) {
            return rc;
        }
    }
}