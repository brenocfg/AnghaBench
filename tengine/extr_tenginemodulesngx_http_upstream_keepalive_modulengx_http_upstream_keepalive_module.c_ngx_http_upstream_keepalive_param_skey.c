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
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_7__ {int /*<<< orphan*/ * slice_key; } ;
typedef  TYPE_1__ ngx_http_upstream_keepalive_srv_conf_t ;
typedef  int /*<<< orphan*/  ngx_http_complex_value_t ;
struct TYPE_8__ {int /*<<< orphan*/ * complex_value; int /*<<< orphan*/ * value; TYPE_3__* cf; } ;
typedef  TYPE_2__ ngx_http_compile_complex_value_t ;
struct TYPE_9__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ ngx_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  ngx_http_compile_complex_value (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * ngx_palloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_keepalive_param_skey(ngx_conf_t *cf, void *conf,
    ngx_str_t *val)
{
    ngx_http_compile_complex_value_t         ccv;
    ngx_http_upstream_keepalive_srv_conf_t  *kcf = conf;

    kcf->slice_key = ngx_palloc(cf->pool,
                                sizeof(ngx_http_complex_value_t));
    if (kcf->slice_key == NULL) {
        return NGX_ERROR;
    }

    ngx_memzero(&ccv, sizeof(ngx_http_compile_complex_value_t));

    ccv.cf = cf;
    ccv.value = val;
    ccv.complex_value = kcf->slice_key;

    return ngx_http_compile_complex_value(&ccv);
}