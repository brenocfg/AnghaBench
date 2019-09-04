#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_10__ {int /*<<< orphan*/  content_type; int /*<<< orphan*/  content_type_len; } ;
struct TYPE_13__ {TYPE_4__* parent; TYPE_2__ headers_out; int /*<<< orphan*/  header_sent; int /*<<< orphan*/  args; int /*<<< orphan*/  uri; TYPE_1__* connection; scalar_t__ request_output; } ;
typedef  TYPE_5__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_chain_t ;
struct TYPE_11__ {int /*<<< orphan*/  content_type; int /*<<< orphan*/  content_type_len; } ;
struct TYPE_12__ {TYPE_3__ headers_out; } ;
struct TYPE_9__ {int /*<<< orphan*/  log; scalar_t__ error; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ ngx_http_output_filter (TYPE_5__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_http_send_header (TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_ssi_stub_output(ngx_http_request_t *r, void *data, ngx_int_t rc)
{
    ngx_chain_t  *out;

    if (rc == NGX_ERROR || r->connection->error || r->request_output) {
        return rc;
    }

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "ssi stub output: \"%V?%V\"", &r->uri, &r->args);

    out = data;

    if (!r->header_sent) {
        r->headers_out.content_type_len =
                                      r->parent->headers_out.content_type_len;
        r->headers_out.content_type = r->parent->headers_out.content_type;

        if (ngx_http_send_header(r) == NGX_ERROR) {
            return NGX_ERROR;
        }
    }

    return ngx_http_output_filter(r, out);
}