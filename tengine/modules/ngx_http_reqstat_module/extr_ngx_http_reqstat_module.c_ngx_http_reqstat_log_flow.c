#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
typedef  int const ngx_int_t ;
struct TYPE_10__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_9__ {size_t nelts; int /*<<< orphan*/ ** elts; } ;
struct TYPE_11__ {size_t sent; TYPE_2__ monitor_index; } ;
typedef  TYPE_4__ ngx_http_reqstat_store_t ;
typedef  int /*<<< orphan*/  ngx_http_reqstat_rbnode_t ;
typedef  int /*<<< orphan*/  ngx_http_reqstat_conf_t ;
struct TYPE_8__ {size_t sent; } ;

/* Variables and functions */
#define  NGX_AGAIN 130 
#define  NGX_DECLINED 129 
#define  NGX_ERROR 128 
 int /*<<< orphan*/  NGX_HTTP_REQSTAT_BYTES_OUT ; 
 int const NGX_OK ; 
 int ngx_http_reqstat_check_enable (TYPE_3__*,int /*<<< orphan*/ **,TYPE_4__**) ; 
 int /*<<< orphan*/  ngx_http_reqstat_count (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

ngx_int_t
ngx_http_reqstat_log_flow(ngx_http_request_t *r)
{
    ngx_uint_t                    i, diff;
    ngx_http_reqstat_conf_t      *rcf;
    ngx_http_reqstat_store_t     *store;
    ngx_http_reqstat_rbnode_t    *fnode, **fnode_store;

    switch (ngx_http_reqstat_check_enable(r, &rcf, &store)) {
        case NGX_ERROR:
            return NGX_ERROR;

        case NGX_DECLINED:
        case NGX_AGAIN:
            return NGX_OK;

        default:
            break;
    }

    diff = r->connection->sent - store->sent;
    store->sent = r->connection->sent;

    fnode_store = store->monitor_index.elts;
    for (i = 0; i < store->monitor_index.nelts; i++) {
        fnode = fnode_store[i];
        if (fnode == NULL) {
            continue;
        }

        ngx_http_reqstat_count(fnode, NGX_HTTP_REQSTAT_BYTES_OUT, diff);
    }

    return NGX_OK;
}