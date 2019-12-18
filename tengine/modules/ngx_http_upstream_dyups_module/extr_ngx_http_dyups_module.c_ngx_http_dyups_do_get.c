#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_26__ {int len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_25__ {scalar_t__ content_length_n; scalar_t__ status; } ;
struct TYPE_27__ {TYPE_1__ headers_out; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_28__ {scalar_t__ deleted; } ;
typedef  TYPE_4__ ngx_http_dyups_srv_conf_t ;
struct TYPE_29__ {int /*<<< orphan*/ * next; TYPE_6__* buf; } ;
typedef  TYPE_5__ ngx_chain_t ;
struct TYPE_30__ {int last_buf; } ;
typedef  TYPE_6__ ngx_buf_t ;
struct TYPE_31__ {int nelts; TYPE_2__* elts; } ;
typedef  TYPE_7__ ngx_array_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_FLUSH ; 
 scalar_t__ NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 scalar_t__ NGX_HTTP_NOT_FOUND ; 
 scalar_t__ NGX_HTTP_NO_CONTENT ; 
 scalar_t__ NGX_HTTP_OK ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_buf_size (TYPE_6__*) ; 
 TYPE_4__* ngx_dyups_find_upstream (TYPE_2__*,scalar_t__*) ; 
 scalar_t__ ngx_http_discard_request_body (TYPE_3__*) ; 
 TYPE_6__* ngx_http_dyups_show_detail (TYPE_3__*) ; 
 TYPE_6__* ngx_http_dyups_show_list (TYPE_3__*) ; 
 TYPE_6__* ngx_http_dyups_show_upstream (TYPE_3__*,TYPE_4__*) ; 
 scalar_t__ ngx_http_output_filter (TYPE_3__*,TYPE_5__*) ; 
 scalar_t__ ngx_http_send_header (TYPE_3__*) ; 
 scalar_t__ ngx_http_send_special (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_dyups_do_get(ngx_http_request_t *r, ngx_array_t *resource)
{
    ngx_int_t                   rc, status, dumy;
    ngx_buf_t                  *buf;
    ngx_str_t                  *value;
    ngx_chain_t                 out;
    ngx_http_dyups_srv_conf_t  *duscf;

    rc = ngx_http_discard_request_body(r);
    if (rc != NGX_OK) {
        return rc;
    }

    if (resource->nelts == 0) {
        return NGX_HTTP_NOT_FOUND;
    }

    buf = NULL;
    value = resource->elts;

    if (value[0].len == 4
        && ngx_strncasecmp(value[0].data, (u_char *) "list", 4) == 0)
    {
        buf = ngx_http_dyups_show_list(r);
        if (buf == NULL) {
            status = NGX_HTTP_INTERNAL_SERVER_ERROR;
            goto finish;
        }
    }

    if (value[0].len == 6
        && ngx_strncasecmp(value[0].data, (u_char *) "detail", 6) == 0)
    {
        buf = ngx_http_dyups_show_detail(r);
        if (buf == NULL) {
            status = NGX_HTTP_INTERNAL_SERVER_ERROR;
            goto finish;
        }
    }

    if (value[0].len == 8
        && ngx_strncasecmp(value[0].data, (u_char *) "upstream", 8) == 0)
    {
        if (resource->nelts != 2) {
            status = NGX_HTTP_NOT_FOUND;
            goto finish;
        }

        duscf = ngx_dyups_find_upstream(&value[1], &dumy);
        if (duscf == NULL || duscf->deleted) {
            status = NGX_HTTP_NOT_FOUND;
            goto finish;
        }

        buf = ngx_http_dyups_show_upstream(r, duscf);
        if (buf == NULL) {
            status = NGX_HTTP_INTERNAL_SERVER_ERROR;
            goto finish;
        }
    }

    if (buf != NULL && ngx_buf_size(buf) == 0) {
        status = NGX_HTTP_NO_CONTENT;
    } else {
        status = buf ? NGX_HTTP_OK : NGX_HTTP_NOT_FOUND;
    }

finish:

    r->headers_out.status = status;

    if (status != NGX_HTTP_OK) {
        r->headers_out.content_length_n = 0;
    } else {
        r->headers_out.content_length_n = ngx_buf_size(buf);
    }

    rc = ngx_http_send_header(r);
    if (rc == NGX_ERROR || rc > NGX_OK) {
        return rc;
    }

    if (status != NGX_HTTP_OK) {
        return ngx_http_send_special(r, NGX_HTTP_FLUSH);
    }

    buf->last_buf = 1;
    out.buf = buf;
    out.next = NULL;

    return ngx_http_output_filter(r, &out);
}