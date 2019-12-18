#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_14__ {scalar_t__ len; } ;
struct TYPE_21__ {scalar_t__ content_length_n; int chunked; scalar_t__ connection_type; TYPE_6__* keep_alive; int /*<<< orphan*/  keep_alive_n; TYPE_4__* transfer_encoding; TYPE_2__* content_length; int /*<<< orphan*/ * host; TYPE_11__ server; } ;
struct TYPE_23__ {scalar_t__ http_version; scalar_t__ method; TYPE_7__ headers_in; TYPE_3__* connection; } ;
typedef  TYPE_9__ ngx_http_request_t ;
struct TYPE_22__ {int len; int /*<<< orphan*/  data; } ;
struct TYPE_19__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_20__ {TYPE_5__ value; } ;
struct TYPE_18__ {TYPE_8__ value; } ;
struct TYPE_17__ {int /*<<< orphan*/  log; } ;
struct TYPE_15__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_16__ {TYPE_1__ value; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_BAD_REQUEST ; 
 scalar_t__ NGX_HTTP_CONNECTION_KEEP_ALIVE ; 
 int /*<<< orphan*/  NGX_HTTP_NOT_ALLOWED ; 
 int /*<<< orphan*/  NGX_HTTP_NOT_IMPLEMENTED ; 
 scalar_t__ NGX_HTTP_TRACE ; 
 scalar_t__ NGX_HTTP_VERSION_10 ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_atoof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_atotm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_finalize_request (TYPE_9__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_set_virtual_server (TYPE_9__*,TYPE_11__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ngx_strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

ngx_int_t
ngx_http_process_request_header(ngx_http_request_t *r)
{
    if (r->headers_in.server.len == 0
        && ngx_http_set_virtual_server(r, &r->headers_in.server)
           == NGX_ERROR)
    {
        return NGX_ERROR;
    }

    if (r->headers_in.host == NULL && r->http_version > NGX_HTTP_VERSION_10) {
        ngx_log_error(NGX_LOG_INFO, r->connection->log, 0,
                   "client sent HTTP/1.1 request without \"Host\" header");
        ngx_http_finalize_request(r, NGX_HTTP_BAD_REQUEST);
        return NGX_ERROR;
    }

    if (r->headers_in.content_length) {
        r->headers_in.content_length_n =
                            ngx_atoof(r->headers_in.content_length->value.data,
                                      r->headers_in.content_length->value.len);

        if (r->headers_in.content_length_n == NGX_ERROR) {
            ngx_log_error(NGX_LOG_INFO, r->connection->log, 0,
                          "client sent invalid \"Content-Length\" header");
            ngx_http_finalize_request(r, NGX_HTTP_BAD_REQUEST);
            return NGX_ERROR;
        }
    }

    if (r->method == NGX_HTTP_TRACE) {
        ngx_log_error(NGX_LOG_INFO, r->connection->log, 0,
                      "client sent TRACE method");
        ngx_http_finalize_request(r, NGX_HTTP_NOT_ALLOWED);
        return NGX_ERROR;
    }

    if (r->headers_in.transfer_encoding) {
        if (r->headers_in.transfer_encoding->value.len == 7
            && ngx_strncasecmp(r->headers_in.transfer_encoding->value.data,
                               (u_char *) "chunked", 7) == 0)
        {
            r->headers_in.content_length = NULL;
            r->headers_in.content_length_n = -1;
            r->headers_in.chunked = 1;

        } else if (r->headers_in.transfer_encoding->value.len != 8
            || ngx_strncasecmp(r->headers_in.transfer_encoding->value.data,
                               (u_char *) "identity", 8) != 0)
        {
            ngx_log_error(NGX_LOG_INFO, r->connection->log, 0,
                          "client sent unknown \"Transfer-Encoding\": \"%V\"",
                          &r->headers_in.transfer_encoding->value);
            ngx_http_finalize_request(r, NGX_HTTP_NOT_IMPLEMENTED);
            return NGX_ERROR;
        }
    }

    if (r->headers_in.connection_type == NGX_HTTP_CONNECTION_KEEP_ALIVE) {
        if (r->headers_in.keep_alive) {
            r->headers_in.keep_alive_n =
                            ngx_atotm(r->headers_in.keep_alive->value.data,
                                      r->headers_in.keep_alive->value.len);
        }
    }

    return NGX_OK;
}