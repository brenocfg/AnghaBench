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
typedef  int /*<<< orphan*/  ngx_http_upstream_check_peer_t ;
struct TYPE_6__ {TYPE_2__* data; } ;
typedef  TYPE_1__ ngx_event_t ;
struct TYPE_7__ {int error; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ ngx_connection_t ;

/* Variables and functions */
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_http_upstream_check_clean_event (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_upstream_check_finish_handler (TYPE_1__*) ; 
 scalar_t__ ngx_http_upstream_check_need_exit () ; 
 scalar_t__ ngx_http_upstream_check_peek_one_byte (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_check_status_update (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
ngx_http_upstream_check_peek_handler(ngx_event_t *event)
{
    ngx_connection_t               *c;
    ngx_http_upstream_check_peer_t *peer;

    if (ngx_http_upstream_check_need_exit()) {
        return;
    }

    c = event->data;
    peer = c->data;

    if (ngx_http_upstream_check_peek_one_byte(c) == NGX_OK) {
        ngx_http_upstream_check_status_update(peer, 1);

    } else {
        c->error = 1;
        ngx_http_upstream_check_status_update(peer, 0);
    }

    ngx_http_upstream_check_clean_event(peer);

    ngx_http_upstream_check_finish_handler(event);
}