#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ len; scalar_t__ data; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_9__ {scalar_t__ len; } ;
struct TYPE_12__ {scalar_t__ uri_start; scalar_t__ uri_end; TYPE_2__* connection; TYPE_1__ unparsed_uri; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_10__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_ABORT ; 
 scalar_t__ NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_parse_uri (TYPE_4__*) ; 
 scalar_t__ ngx_http_process_request_uri (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static ngx_int_t
ngx_http_v2_parse_path(ngx_http_request_t *r, ngx_str_t *value)
{
    if (r->unparsed_uri.len) {
        ngx_log_error(NGX_LOG_INFO, r->connection->log, 0,
                      "client sent duplicate :path header");

        return NGX_DECLINED;
    }

    if (value->len == 0) {
        ngx_log_error(NGX_LOG_INFO, r->connection->log, 0,
                      "client sent empty :path header");

        return NGX_DECLINED;
    }

    r->uri_start = value->data;
    r->uri_end = value->data + value->len;

    if (ngx_http_parse_uri(r) != NGX_OK) {
        ngx_log_error(NGX_LOG_INFO, r->connection->log, 0,
                      "client sent invalid :path header: \"%V\"", value);

        return NGX_DECLINED;
    }

    if (ngx_http_process_request_uri(r) != NGX_OK) {
        /*
         * request has been finalized already
         * in ngx_http_process_request_uri()
         */
        return NGX_ABORT;
    }

    return NGX_OK;
}