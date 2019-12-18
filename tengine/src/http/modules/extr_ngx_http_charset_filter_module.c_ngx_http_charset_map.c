#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  void* u_char ;
typedef  int ngx_uint_t ;
struct TYPE_11__ {int len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  int ngx_int_t ;
struct TYPE_12__ {void** src2dst; void** dst2src; } ;
typedef  TYPE_4__ ngx_http_charset_tables_t ;
struct TYPE_13__ {int /*<<< orphan*/  characters; TYPE_2__* charset; TYPE_4__* table; } ;
typedef  TYPE_5__ ngx_http_charset_conf_ctx_t ;
struct TYPE_14__ {int /*<<< orphan*/  pool; TYPE_5__* ctx; TYPE_1__* args; } ;
typedef  TYPE_6__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_10__ {int length; scalar_t__ utf8; } ;
struct TYPE_9__ {int nelts; TYPE_3__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int NGX_UTF_LEN ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,char*,...) ; 
 int ngx_hextoi (int /*<<< orphan*/ *,int) ; 
 void** ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int ngx_utf8_decode (void***,int) ; 

__attribute__((used)) static char *
ngx_http_charset_map(ngx_conf_t *cf, ngx_command_t *dummy, void *conf)
{
    u_char                       *p, *dst2src, **pp;
    uint32_t                      n;
    ngx_int_t                     src, dst;
    ngx_str_t                    *value;
    ngx_uint_t                    i;
    ngx_http_charset_tables_t    *table;
    ngx_http_charset_conf_ctx_t  *ctx;

    if (cf->args->nelts != 2) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "invalid parameters number");
        return NGX_CONF_ERROR;
    }

    value = cf->args->elts;

    src = ngx_hextoi(value[0].data, value[0].len);
    if (src == NGX_ERROR || src > 255) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid value \"%V\"", &value[0]);
        return NGX_CONF_ERROR;
    }

    ctx = cf->ctx;
    table = ctx->table;

    if (ctx->charset->utf8) {
        p = &table->src2dst[src * NGX_UTF_LEN];

        *p++ = (u_char) (value[1].len / 2);

        for (i = 0; i < value[1].len; i += 2) {
            dst = ngx_hextoi(&value[1].data[i], 2);
            if (dst == NGX_ERROR || dst > 255) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "invalid value \"%V\"", &value[1]);
                return NGX_CONF_ERROR;
            }

            *p++ = (u_char) dst;
        }

        i /= 2;

        ctx->charset->length += i;
        ctx->characters++;

        p = &table->src2dst[src * NGX_UTF_LEN] + 1;

        n = ngx_utf8_decode(&p, i);

        if (n > 0xffff) {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "invalid value \"%V\"", &value[1]);
            return NGX_CONF_ERROR;
        }

        pp = (u_char **) &table->dst2src[0];

        dst2src = pp[n >> 8];

        if (dst2src == NULL) {
            dst2src = ngx_pcalloc(cf->pool, 256);
            if (dst2src == NULL) {
                return NGX_CONF_ERROR;
            }

            pp[n >> 8] = dst2src;
        }

        dst2src[n & 0xff] = (u_char) src;

    } else {
        dst = ngx_hextoi(value[1].data, value[1].len);
        if (dst == NGX_ERROR || dst > 255) {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "invalid value \"%V\"", &value[1]);
            return NGX_CONF_ERROR;
        }

        table->src2dst[src] = (u_char) dst;
        table->dst2src[dst] = (u_char) src;
    }

    return NGX_CONF_OK;
}