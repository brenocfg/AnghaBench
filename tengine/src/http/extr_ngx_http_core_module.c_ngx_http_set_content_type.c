#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_12__ {scalar_t__ len; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_11__ {TYPE_3__ content_type; scalar_t__ content_type_len; } ;
struct TYPE_10__ {size_t len; char* data; } ;
struct TYPE_13__ {TYPE_2__ headers_out; TYPE_1__ exten; int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_14__ {TYPE_3__ default_type; int /*<<< orphan*/  types_hash; } ;
typedef  TYPE_5__ ngx_http_core_loc_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 size_t ngx_hash (size_t,char) ; 
 TYPE_3__* ngx_hash_find (int /*<<< orphan*/ *,size_t,char*,size_t) ; 
 size_t ngx_hash_strlow (char*,char*,size_t) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_5__* ngx_http_get_module_loc_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 char* ngx_pnalloc (int /*<<< orphan*/ ,size_t) ; 

ngx_int_t
ngx_http_set_content_type(ngx_http_request_t *r)
{
    u_char                     c, *exten;
    ngx_str_t                 *type;
    ngx_uint_t                 i, hash;
    ngx_http_core_loc_conf_t  *clcf;

    if (r->headers_out.content_type.len) {
        return NGX_OK;
    }

    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

    if (r->exten.len) {

        hash = 0;

        for (i = 0; i < r->exten.len; i++) {
            c = r->exten.data[i];

            if (c >= 'A' && c <= 'Z') {

                exten = ngx_pnalloc(r->pool, r->exten.len);
                if (exten == NULL) {
                    return NGX_ERROR;
                }

                hash = ngx_hash_strlow(exten, r->exten.data, r->exten.len);

                r->exten.data = exten;

                break;
            }

            hash = ngx_hash(hash, c);
        }

        type = ngx_hash_find(&clcf->types_hash, hash,
                             r->exten.data, r->exten.len);

        if (type) {
            r->headers_out.content_type_len = type->len;
            r->headers_out.content_type = *type;

            return NGX_OK;
        }
    }

    r->headers_out.content_type_len = clcf->default_type.len;
    r->headers_out.content_type = clcf->default_type;

    return NGX_OK;
}