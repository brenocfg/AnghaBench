#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_7__ {char* action; } ;
typedef  TYPE_1__ ngx_log_t ;
struct TYPE_8__ {TYPE_3__* connection; } ;
typedef  TYPE_2__ ngx_http_v2_connection_t ;
struct TYPE_9__ {TYPE_1__* log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_V2_PROTOCOL_ERROR ; 
 int /*<<< orphan*/ * ngx_http_v2_connection_error (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_http_v2_state_preface (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_proxy_protocol_read (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u_char *
ngx_http_v2_state_proxy_protocol(ngx_http_v2_connection_t *h2c, u_char *pos,
    u_char *end)
{
    ngx_log_t  *log;

    log = h2c->connection->log;
    log->action = "reading PROXY protocol";

    pos = ngx_proxy_protocol_read(h2c->connection, pos, end);

    log->action = "processing HTTP/2 connection";

    if (pos == NULL) {
        return ngx_http_v2_connection_error(h2c, NGX_HTTP_V2_PROTOCOL_ERROR);
    }

    return ngx_http_v2_state_preface(h2c, pos, end);
}