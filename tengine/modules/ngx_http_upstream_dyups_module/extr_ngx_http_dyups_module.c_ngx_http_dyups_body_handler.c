#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_18__ {int len; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_19__ {scalar_t__ method; TYPE_2__* connection; TYPE_1__* request_body; int /*<<< orphan*/  uri; int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_buf_t ;
struct TYPE_20__ {int nelts; TYPE_3__* elts; } ;
typedef  TYPE_5__ ngx_array_t ;
struct TYPE_17__ {int /*<<< orphan*/  log; } ;
struct TYPE_16__ {scalar_t__ temp_file; int /*<<< orphan*/ * bufs; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_NOT_ALLOWED ; 
 int /*<<< orphan*/  NGX_HTTP_NOT_FOUND ; 
 int /*<<< orphan*/  NGX_HTTP_NO_CONTENT ; 
 scalar_t__ NGX_HTTP_POST ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 TYPE_5__* ngx_dyups_parse_path (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_dyups_update_upstream (TYPE_3__*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * ngx_http_dyups_read_body (TYPE_4__*) ; 
 int /*<<< orphan*/ * ngx_http_dyups_read_body_from_file (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_dyups_send_response (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_str_set (TYPE_3__*,char*) ; 
 scalar_t__ ngx_strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
ngx_http_dyups_body_handler(ngx_http_request_t *r)
{
    ngx_str_t                   *value, rv, name;
    ngx_int_t                    status;
    ngx_buf_t                   *body;
    ngx_array_t                 *res;

    ngx_str_set(&rv, "");

    if (r->method != NGX_HTTP_POST) {
        status = NGX_HTTP_NOT_ALLOWED;
        goto finish;
    }

    res = ngx_dyups_parse_path(r->pool, &r->uri);
    if (res == NULL) {
        ngx_str_set(&rv, "out of memory");
        status = NGX_HTTP_INTERNAL_SERVER_ERROR;
        goto finish;
    }

    if (r->request_body == NULL || r->request_body->bufs == NULL) {
        status = NGX_HTTP_NO_CONTENT;
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "[dyups] interface no content");
        ngx_str_set(&rv, "no content\n");
        goto finish;
    }

    if (r->request_body->temp_file) {

        body = ngx_http_dyups_read_body_from_file(r);
    } else {

        body = ngx_http_dyups_read_body(r);
    }

    if (body == NULL) {
        status = NGX_HTTP_INTERNAL_SERVER_ERROR;
        ngx_str_set(&rv, "out of memory\n");
        goto finish;
    }

    if (res->nelts != 2) {
        ngx_str_set(&rv, "not support this interface");
        status = NGX_HTTP_NOT_FOUND;
        goto finish;
    }

    /*
      url: /upstream
      body: server ip:port weight
    */

    value = res->elts;

    if (value[0].len != 8
        || ngx_strncasecmp(value[0].data, (u_char *) "upstream", 8) != 0)
    {
        ngx_str_set(&rv, "not support this api");
        status = NGX_HTTP_NOT_FOUND;
        goto finish;
    }

    name = value[1];

    ngx_log_error(NGX_LOG_INFO, r->connection->log, 0,
                  "[dyups] post upstream name: %V", &name);

    status = ngx_dyups_update_upstream(&name, body, &rv);

finish:

    ngx_http_dyups_send_response(r, status, &rv);
}