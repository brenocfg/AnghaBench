#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_15__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_16__ {TYPE_1__ name; } ;
typedef  TYPE_2__ ngx_http_header_t ;
struct TYPE_17__ {int /*<<< orphan*/  headers_in_hash; } ;
typedef  TYPE_3__ ngx_http_core_main_conf_t ;
struct TYPE_18__ {TYPE_2__* value; int /*<<< orphan*/  key_hash; TYPE_1__ key; } ;
typedef  TYPE_4__ ngx_hash_key_t ;
struct TYPE_19__ {int max_size; char* name; int /*<<< orphan*/ * temp_pool; int /*<<< orphan*/  pool; int /*<<< orphan*/  bucket_size; int /*<<< orphan*/  (* key ) (int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/ * hash; } ;
typedef  TYPE_5__ ngx_hash_init_t ;
struct TYPE_20__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  temp_pool; } ;
typedef  TYPE_6__ ngx_conf_t ;
struct TYPE_21__ {int /*<<< orphan*/  nelts; int /*<<< orphan*/  elts; } ;
typedef  TYPE_7__ ngx_array_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_align (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_array_init (TYPE_7__*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_4__* ngx_array_push (TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_cacheline_size ; 
 scalar_t__ ngx_hash_init (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_hash_key_lc (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_2__* ngx_http_headers_in ; 

__attribute__((used)) static ngx_int_t
ngx_http_init_headers_in_hash(ngx_conf_t *cf, ngx_http_core_main_conf_t *cmcf)
{
    ngx_array_t         headers_in;
    ngx_hash_key_t     *hk;
    ngx_hash_init_t     hash;
    ngx_http_header_t  *header;

    if (ngx_array_init(&headers_in, cf->temp_pool, 32, sizeof(ngx_hash_key_t))
        != NGX_OK)
    {
        return NGX_ERROR;
    }

    for (header = ngx_http_headers_in; header->name.len; header++) {
        hk = ngx_array_push(&headers_in);
        if (hk == NULL) {
            return NGX_ERROR;
        }

        hk->key = header->name;
        hk->key_hash = ngx_hash_key_lc(header->name.data, header->name.len);
        hk->value = header;
    }

    hash.hash = &cmcf->headers_in_hash;
    hash.key = ngx_hash_key_lc;
    hash.max_size = 512;
    hash.bucket_size = ngx_align(64, ngx_cacheline_size);
    hash.name = "headers_in_hash";
    hash.pool = cf->pool;
    hash.temp_pool = NULL;

    if (ngx_hash_init(&hash, headers_in.elts, headers_in.nelts) != NGX_OK) {
        return NGX_ERROR;
    }

    return NGX_OK;
}