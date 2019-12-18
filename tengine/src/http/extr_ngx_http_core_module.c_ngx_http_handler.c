#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int connection_type; scalar_t__ content_length_n; scalar_t__ chunked; } ;
struct TYPE_15__ {int keepalive; int lingering_close; int valid_location; int /*<<< orphan*/  (* write_event_handler ) (TYPE_5__*) ;scalar_t__ gzip_vary; scalar_t__ gzip_ok; scalar_t__ gzip_tested; scalar_t__ phase_handler; TYPE_3__ headers_in; int /*<<< orphan*/  http_version; int /*<<< orphan*/  internal; TYPE_2__* connection; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_14__ {scalar_t__ server_rewrite_index; } ;
struct TYPE_16__ {TYPE_4__ phase_engine; } ;
typedef  TYPE_6__ ngx_http_core_main_conf_t ;
struct TYPE_12__ {TYPE_1__* log; } ;
struct TYPE_11__ {int /*<<< orphan*/ * action; } ;

/* Variables and functions */
#define  NGX_HTTP_CONNECTION_CLOSE 129 
#define  NGX_HTTP_CONNECTION_KEEP_ALIVE 128 
 int /*<<< orphan*/  NGX_HTTP_VERSION_10 ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 int /*<<< orphan*/  ngx_http_core_run_phases (TYPE_5__*) ; 
 TYPE_6__* ngx_http_get_module_main_conf (TYPE_5__*,int /*<<< orphan*/ ) ; 

void
ngx_http_handler(ngx_http_request_t *r)
{
    ngx_http_core_main_conf_t  *cmcf;

    r->connection->log->action = NULL;

    if (!r->internal) {
        switch (r->headers_in.connection_type) {
        case 0:
            r->keepalive = (r->http_version > NGX_HTTP_VERSION_10);
            break;

        case NGX_HTTP_CONNECTION_CLOSE:
            r->keepalive = 0;
            break;

        case NGX_HTTP_CONNECTION_KEEP_ALIVE:
            r->keepalive = 1;
            break;
        }

        r->lingering_close = (r->headers_in.content_length_n > 0
                              || r->headers_in.chunked);
        r->phase_handler = 0;

    } else {
        cmcf = ngx_http_get_module_main_conf(r, ngx_http_core_module);
        r->phase_handler = cmcf->phase_engine.server_rewrite_index;
    }

    r->valid_location = 1;
#if (NGX_HTTP_GZIP)
    r->gzip_tested = 0;
    r->gzip_ok = 0;
    r->gzip_vary = 0;
#endif

    r->write_event_handler = ngx_http_core_run_phases;
    ngx_http_core_run_phases(r);
}