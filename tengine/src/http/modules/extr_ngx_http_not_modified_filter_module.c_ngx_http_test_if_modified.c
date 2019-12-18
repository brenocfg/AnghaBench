#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
typedef  int ngx_uint_t ;
struct TYPE_15__ {scalar_t__ last_modified_time; } ;
struct TYPE_13__ {TYPE_2__* if_modified_since; } ;
struct TYPE_16__ {TYPE_5__ headers_out; TYPE_4__* connection; TYPE_3__ headers_in; } ;
typedef  TYPE_6__ ngx_http_request_t ;
struct TYPE_17__ {scalar_t__ if_modified_since; } ;
typedef  TYPE_7__ ngx_http_core_loc_conf_t ;
struct TYPE_14__ {int /*<<< orphan*/  log; } ;
struct TYPE_11__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_12__ {TYPE_1__ value; } ;

/* Variables and functions */
 scalar_t__ NGX_HTTP_IMS_EXACT ; 
 scalar_t__ NGX_HTTP_IMS_OFF ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_7__* ngx_http_get_module_loc_conf (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ ngx_parse_http_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_uint_t
ngx_http_test_if_modified(ngx_http_request_t *r)
{
    time_t                     ims;
    ngx_http_core_loc_conf_t  *clcf;

    if (r->headers_out.last_modified_time == (time_t) -1) {
        return 1;
    }

    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

    if (clcf->if_modified_since == NGX_HTTP_IMS_OFF) {
        return 1;
    }

    ims = ngx_parse_http_time(r->headers_in.if_modified_since->value.data,
                              r->headers_in.if_modified_since->value.len);

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http ims:%T lm:%T", ims, r->headers_out.last_modified_time);

    if (ims == r->headers_out.last_modified_time) {
        return 0;
    }

    if (clcf->if_modified_since == NGX_HTTP_IMS_EXACT
        || ims < r->headers_out.last_modified_time)
    {
        return 1;
    }

    return 0;
}