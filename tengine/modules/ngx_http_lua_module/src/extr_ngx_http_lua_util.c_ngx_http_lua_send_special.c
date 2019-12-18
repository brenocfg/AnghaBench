#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_6__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_5__ {TYPE_2__* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_http_send_special (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_send_special(ngx_http_request_t *r, ngx_uint_t flags)
{
    ngx_int_t            rc;
    ngx_http_request_t  *ar; /* active request */

    ar = r->connection->data;

    if (ar != r) {

        /* bypass ngx_http_postpone_filter_module */

        r->connection->data = r;
        rc = ngx_http_send_special(r, flags);
        r->connection->data = ar;
        return rc;
    }

    return ngx_http_send_special(r, flags);
}