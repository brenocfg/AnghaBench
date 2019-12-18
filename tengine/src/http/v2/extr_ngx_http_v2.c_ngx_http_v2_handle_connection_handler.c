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
struct TYPE_9__ {scalar_t__ last_out; } ;
typedef  TYPE_1__ ngx_http_v2_connection_t ;
struct TYPE_10__ {scalar_t__ ready; int /*<<< orphan*/  (* handler ) (TYPE_2__*) ;TYPE_3__* data; int /*<<< orphan*/  log; } ;
typedef  TYPE_2__ ngx_event_t ;
struct TYPE_11__ {TYPE_1__* data; scalar_t__ error; } ;
typedef  TYPE_3__ ngx_connection_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  ngx_http_v2_finalize_connection (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_v2_handle_connection (TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_http_v2_read_handler (TYPE_2__*) ; 
 scalar_t__ ngx_http_v2_send_output_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ngx_http_v2_handle_connection_handler(ngx_event_t *rev)
{
    ngx_connection_t          *c;
    ngx_http_v2_connection_t  *h2c;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, rev->log, 0,
                   "http2 handle connection handler");

    c = rev->data;
    h2c = c->data;

    if (c->error) {
        ngx_http_v2_finalize_connection(h2c, 0);
        return;
    }

    rev->handler = ngx_http_v2_read_handler;

    if (rev->ready) {
        ngx_http_v2_read_handler(rev);
        return;
    }

    if (h2c->last_out && ngx_http_v2_send_output_queue(h2c) == NGX_ERROR) {
        ngx_http_v2_finalize_connection(h2c, 0);
        return;
    }

    ngx_http_v2_handle_connection(c->data);
}