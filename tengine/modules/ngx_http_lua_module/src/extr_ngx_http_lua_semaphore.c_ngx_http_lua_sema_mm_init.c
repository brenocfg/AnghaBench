#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_7__ {int num_per_block; scalar_t__ used; scalar_t__ total; scalar_t__ cur_epoch; int /*<<< orphan*/  free_queue; TYPE_2__* lmcf; } ;
typedef  TYPE_1__ ngx_http_lua_sema_mm_t ;
struct TYPE_8__ {TYPE_1__* sema_mm; } ;
typedef  TYPE_2__ ngx_http_lua_main_conf_t ;
struct TYPE_9__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ ngx_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_1__* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_queue_init (int /*<<< orphan*/ *) ; 

ngx_int_t
ngx_http_lua_sema_mm_init(ngx_conf_t *cf, ngx_http_lua_main_conf_t *lmcf)
{
    ngx_http_lua_sema_mm_t *mm;

    mm = ngx_palloc(cf->pool, sizeof(ngx_http_lua_sema_mm_t));
    if (mm == NULL) {
        return NGX_ERROR;
    }

    lmcf->sema_mm = mm;
    mm->lmcf = lmcf;

    ngx_queue_init(&mm->free_queue);
    mm->cur_epoch = 0;
    mm->total = 0;
    mm->used = 0;

    /* it's better to be 4096, but it needs some space for
     * ngx_http_lua_sema_mm_block_t, one is enough, so it is 4095
     */
    mm->num_per_block = 4095;

    return NGX_OK;
}