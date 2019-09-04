#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_15__ {TYPE_2__* www_authenticate; } ;
struct TYPE_16__ {scalar_t__ access_code; scalar_t__ phase_handler; TYPE_3__ headers_out; TYPE_1__* connection; struct TYPE_16__* main; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_17__ {scalar_t__ (* handler ) (TYPE_4__*) ;scalar_t__ next; } ;
typedef  TYPE_5__ ngx_http_phase_handler_t ;
struct TYPE_18__ {scalar_t__ satisfy; } ;
typedef  TYPE_6__ ngx_http_core_loc_conf_t ;
struct TYPE_14__ {scalar_t__ hash; } ;
struct TYPE_13__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_DONE ; 
 scalar_t__ NGX_HTTP_FORBIDDEN ; 
 scalar_t__ NGX_HTTP_SATISFY_ALL ; 
 scalar_t__ NGX_HTTP_UNAUTHORIZED ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 int /*<<< orphan*/  ngx_http_finalize_request (TYPE_4__*,scalar_t__) ; 
 TYPE_6__* ngx_http_get_module_loc_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ stub1 (TYPE_4__*) ; 

ngx_int_t
ngx_http_core_access_phase(ngx_http_request_t *r, ngx_http_phase_handler_t *ph)
{
    ngx_int_t                  rc;
    ngx_http_core_loc_conf_t  *clcf;

    if (r != r->main) {
        r->phase_handler = ph->next;
        return NGX_AGAIN;
    }

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "access phase: %ui", r->phase_handler);

    rc = ph->handler(r);

    if (rc == NGX_DECLINED) {
        r->phase_handler++;
        return NGX_AGAIN;
    }

    if (rc == NGX_AGAIN || rc == NGX_DONE) {
        return NGX_OK;
    }

    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

    if (clcf->satisfy == NGX_HTTP_SATISFY_ALL) {

        if (rc == NGX_OK) {
            r->phase_handler++;
            return NGX_AGAIN;
        }

    } else {
        if (rc == NGX_OK) {
            r->access_code = 0;

            if (r->headers_out.www_authenticate) {
                r->headers_out.www_authenticate->hash = 0;
            }

            r->phase_handler = ph->next;
            return NGX_AGAIN;
        }

        if (rc == NGX_HTTP_FORBIDDEN || rc == NGX_HTTP_UNAUTHORIZED) {
            if (r->access_code != NGX_HTTP_UNAUTHORIZED) {
                r->access_code = rc;
            }

            r->phase_handler++;
            return NGX_AGAIN;
        }
    }

    /* rc == NGX_ERROR || rc == NGX_HTTP_...  */

    ngx_http_finalize_request(r, rc);
    return NGX_OK;
}