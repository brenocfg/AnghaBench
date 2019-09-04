#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_mail_session_t ;
struct TYPE_5__ {TYPE_2__* data; int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ ngx_event_t ;
struct TYPE_6__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_MAIL ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_handle_write_event (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_mail_proxy_close_session (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ngx_mail_proxy_dummy_handler(ngx_event_t *wev)
{
    ngx_connection_t    *c;
    ngx_mail_session_t  *s;

    ngx_log_debug0(NGX_LOG_DEBUG_MAIL, wev->log, 0, "mail proxy dummy handler");

    if (ngx_handle_write_event(wev, 0) != NGX_OK) {
        c = wev->data;
        s = c->data;

        ngx_mail_proxy_close_session(s);
    }
}