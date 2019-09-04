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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_5__ {int /*<<< orphan*/ * json_output; TYPE_2__* out_bufs; int /*<<< orphan*/  pool; int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ ngx_http_tfs_t ;
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_2__ ngx_chain_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_2__* ngx_http_tfs_json_appid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_http_tfs_json_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_http_tfs_set_output_appid(ngx_http_tfs_t *t, uint64_t app_id)
{
    ngx_chain_t  *cl, **ll;

    t->json_output = ngx_http_tfs_json_init(t->log, t->pool);
    if (t->json_output == NULL) {
        return NGX_ERROR;
    }

    for (cl = t->out_bufs, ll = &t->out_bufs; cl; cl = cl->next) {
        ll = &cl->next;
    }

    cl = ngx_http_tfs_json_appid(t->json_output, app_id);
    if (cl == NULL) {
        return NGX_ERROR;
    }

    *ll = cl;
    return NGX_OK;
}