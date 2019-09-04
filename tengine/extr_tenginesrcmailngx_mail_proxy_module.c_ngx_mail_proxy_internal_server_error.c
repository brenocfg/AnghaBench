#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* proxy; TYPE_1__* connection; } ;
typedef  TYPE_4__ ngx_mail_session_t ;
struct TYPE_12__ {int /*<<< orphan*/  fd; } ;
struct TYPE_9__ {TYPE_7__* connection; } ;
struct TYPE_10__ {TYPE_2__ upstream; } ;
struct TYPE_8__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_MAIL ; 
 int /*<<< orphan*/  ngx_close_connection (TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_session_internal_server_error (TYPE_4__*) ; 

__attribute__((used)) static void
ngx_mail_proxy_internal_server_error(ngx_mail_session_t *s)
{
    if (s->proxy->upstream.connection) {
        ngx_log_debug1(NGX_LOG_DEBUG_MAIL, s->connection->log, 0,
                       "close mail proxy connection: %d",
                       s->proxy->upstream.connection->fd);

        ngx_close_connection(s->proxy->upstream.connection);
    }

    ngx_mail_session_internal_server_error(s);
}