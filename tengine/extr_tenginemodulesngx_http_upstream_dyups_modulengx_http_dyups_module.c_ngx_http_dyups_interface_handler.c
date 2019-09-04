#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_7__ {scalar_t__ method; int /*<<< orphan*/  uri; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_event_t ;
typedef  int /*<<< orphan*/  ngx_array_t ;
struct TYPE_8__ {int /*<<< orphan*/  msg_timer; } ;

/* Variables and functions */
 scalar_t__ NGX_HTTP_DELETE ; 
 scalar_t__ NGX_HTTP_GET ; 
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 TYPE_6__ ngx_dyups_global_ctx ; 
 int /*<<< orphan*/ * ngx_dyups_parse_path (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_dyups_do_delete (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_dyups_do_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_dyups_interface_read_body (TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_http_dyups_read_msg (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_dyups_interface_handler(ngx_http_request_t *r)
{
    ngx_array_t  *res;
    ngx_event_t  *timer;

    timer = &ngx_dyups_global_ctx.msg_timer;

    res = ngx_dyups_parse_path(r->pool, &r->uri);
    if (res == NULL) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    if (r->method == NGX_HTTP_GET) {
        ngx_http_dyups_read_msg(timer);
        return ngx_http_dyups_do_get(r, res);
    }

    if (r->method == NGX_HTTP_DELETE) {
        return ngx_http_dyups_do_delete(r, res);
    }

    return ngx_http_dyups_interface_read_body(r);
}