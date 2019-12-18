#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_stream_script_var_code_t ;
typedef  int /*<<< orphan*/  ngx_stream_script_copy_code_t ;
struct TYPE_14__ {int complete_lengths; int complete_values; scalar_t__ root_prefix; scalar_t__ conf_prefix; int /*<<< orphan*/  zero; TYPE_6__** values; TYPE_6__** lengths; TYPE_6__** flushes; TYPE_5__* source; TYPE_1__* cf; } ;
typedef  TYPE_3__ ngx_stream_script_compile_t ;
struct TYPE_15__ {TYPE_2__* complex_value; scalar_t__ root_prefix; scalar_t__ conf_prefix; int /*<<< orphan*/  zero; TYPE_1__* cf; TYPE_5__* value; } ;
typedef  TYPE_4__ ngx_stream_compile_complex_value_t ;
struct TYPE_16__ {size_t len; char* data; } ;
typedef  TYPE_5__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_17__ {int nelts; size_t* elts; } ;
typedef  TYPE_6__ ngx_array_t ;
struct TYPE_13__ {size_t* flushes; size_t* lengths; size_t* values; TYPE_5__ value; } ;
struct TYPE_12__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  cycle; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_array_init (TYPE_6__*,int /*<<< orphan*/ ,size_t,int) ; 
 scalar_t__ ngx_conf_full_name (int /*<<< orphan*/ ,TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_3__*,int) ; 
 scalar_t__ ngx_stream_script_compile (TYPE_3__*) ; 

ngx_int_t
ngx_stream_compile_complex_value(ngx_stream_compile_complex_value_t *ccv)
{
    ngx_str_t                    *v;
    ngx_uint_t                    i, n, nv, nc;
    ngx_array_t                   flushes, lengths, values, *pf, *pl, *pv;
    ngx_stream_script_compile_t   sc;

    v = ccv->value;

    nv = 0;
    nc = 0;

    for (i = 0; i < v->len; i++) {
        if (v->data[i] == '$') {
            if (v->data[i + 1] >= '1' && v->data[i + 1] <= '9') {
                nc++;

            } else {
                nv++;
            }
        }
    }

    if ((v->len == 0 || v->data[0] != '$')
        && (ccv->conf_prefix || ccv->root_prefix))
    {
        if (ngx_conf_full_name(ccv->cf->cycle, v, ccv->conf_prefix) != NGX_OK) {
            return NGX_ERROR;
        }

        ccv->conf_prefix = 0;
        ccv->root_prefix = 0;
    }

    ccv->complex_value->value = *v;
    ccv->complex_value->flushes = NULL;
    ccv->complex_value->lengths = NULL;
    ccv->complex_value->values = NULL;

    if (nv == 0 && nc == 0) {
        return NGX_OK;
    }

    n = nv + 1;

    if (ngx_array_init(&flushes, ccv->cf->pool, n, sizeof(ngx_uint_t))
        != NGX_OK)
    {
        return NGX_ERROR;
    }

    n = nv * (2 * sizeof(ngx_stream_script_copy_code_t)
                  + sizeof(ngx_stream_script_var_code_t))
        + sizeof(uintptr_t);

    if (ngx_array_init(&lengths, ccv->cf->pool, n, 1) != NGX_OK) {
        return NGX_ERROR;
    }

    n = (nv * (2 * sizeof(ngx_stream_script_copy_code_t)
                   + sizeof(ngx_stream_script_var_code_t))
                + sizeof(uintptr_t)
                + v->len
                + sizeof(uintptr_t) - 1)
            & ~(sizeof(uintptr_t) - 1);

    if (ngx_array_init(&values, ccv->cf->pool, n, 1) != NGX_OK) {
        return NGX_ERROR;
    }

    pf = &flushes;
    pl = &lengths;
    pv = &values;

    ngx_memzero(&sc, sizeof(ngx_stream_script_compile_t));

    sc.cf = ccv->cf;
    sc.source = v;
    sc.flushes = &pf;
    sc.lengths = &pl;
    sc.values = &pv;
    sc.complete_lengths = 1;
    sc.complete_values = 1;
    sc.zero = ccv->zero;
    sc.conf_prefix = ccv->conf_prefix;
    sc.root_prefix = ccv->root_prefix;

    if (ngx_stream_script_compile(&sc) != NGX_OK) {
        return NGX_ERROR;
    }

    if (flushes.nelts) {
        ccv->complex_value->flushes = flushes.elts;
        ccv->complex_value->flushes[flushes.nelts] = (ngx_uint_t) -1;
    }

    ccv->complex_value->lengths = lengths.elts;
    ccv->complex_value->values = values.elts;

    return NGX_OK;
}