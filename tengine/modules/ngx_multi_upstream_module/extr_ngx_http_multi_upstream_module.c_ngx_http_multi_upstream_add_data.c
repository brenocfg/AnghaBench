#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  queue; TYPE_3__* data; } ;
typedef  TYPE_1__ ngx_multi_data_t ;
struct TYPE_11__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_multi_connection_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_12__ {int /*<<< orphan*/ * multi_item; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_13__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_2__* ngx_get_multi_connection (TYPE_4__*) ; 
 TYPE_1__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_queue_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_multi_upstream_add_data(ngx_connection_t *c, ngx_http_request_t *r)
{
    ngx_multi_connection_t          *multi_c;
    ngx_multi_data_t                *item_data;

    multi_c = ngx_get_multi_connection(c);
    
    item_data = ngx_pcalloc(c->pool, sizeof(ngx_multi_data_t));
    if (item_data == NULL) {
        return NGX_ERROR;
    }

    item_data->data = r;
    ngx_queue_insert_tail(&multi_c->data, &item_data->queue);
    r->multi_item = &item_data->queue;

    return NGX_OK;
}