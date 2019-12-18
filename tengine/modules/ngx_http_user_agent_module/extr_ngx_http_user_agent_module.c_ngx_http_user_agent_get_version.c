#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  size_t ngx_uint_t ;
struct TYPE_9__ {size_t len; char* data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_http_variable_value_t ;
struct TYPE_10__ {int left; int right; int /*<<< orphan*/ * var; } ;
typedef  TYPE_2__ ngx_http_user_agent_interval_t ;
struct TYPE_11__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ ngx_conf_t ;

/* Variables and functions */
 char NGX_HTTP_UA_MATCH_EXACT ; 
 char NGX_HTTP_UA_MATCH_GE ; 
 char NGX_HTTP_UA_MATCH_INTERVAL ; 
 char NGX_HTTP_UA_MATCH_LE ; 
 int NGX_HTTP_UA_MAX_INT64 ; 
 int NGX_HTTP_UA_MAX_VERSION_VALUE ; 
 int NGX_HTTP_UA_MIN_VERSION_VALUE ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_http_user_agent_interval_t *
ngx_http_user_agent_get_version(ngx_conf_t *cf, ngx_str_t *value)
{
    char                            op;
    uint64_t                        ver, scale, version;
    ngx_uint_t                      i, n;
    ngx_http_user_agent_interval_t *interval;

    op = NGX_HTTP_UA_MATCH_EXACT;
    scale = NGX_HTTP_UA_MAX_INT64;
    version = 0;
    ver = 0;
    n = 0;

    interval = ngx_palloc(cf->pool, sizeof(ngx_http_user_agent_interval_t));
    if(interval == NULL) {
        return NULL;
    }

    interval->var = ngx_pcalloc(cf->pool, sizeof(ngx_http_variable_value_t));
    if (interval->var == NULL) {
        return NULL;
    }

    interval->left = NGX_HTTP_UA_MIN_VERSION_VALUE;
    interval->right = NGX_HTTP_UA_MAX_VERSION_VALUE;

    for (i = 0; i < value->len; i++) {
        if (value->data[i] >= '0' && value->data[i] <= '9') {
            ver = ver * 10 + value->data[i] - '0';
            continue;
        }

        if (value->data[i] == '.') {
            version += ver * scale;
            ver = 0;
            scale /= 10000;

        } else if (value->data[i] == NGX_HTTP_UA_MATCH_LE) {
            if (i != value->len - 1) {
                goto error;
            }

            op = NGX_HTTP_UA_MATCH_LE;
        } else if (value->data[i] == NGX_HTTP_UA_MATCH_EXACT) {
            if (i != value->len - 1) {
                goto error;
            }
        } else if (value->data[i] == NGX_HTTP_UA_MATCH_GE) {
            if (i != value->len - 1) {
                goto error;
            }

            op = NGX_HTTP_UA_MATCH_GE;
        } else if (value->data[i] == NGX_HTTP_UA_MATCH_INTERVAL) {
            op = NGX_HTTP_UA_MATCH_INTERVAL;
            if (n >= 2) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "too many versions");
                return NULL;
            }

            version += ver * scale;
            interval->left = version;
            n++;

            ver = 0;
            scale = NGX_HTTP_UA_MAX_INT64;
            version = 0;

            if (i + 1 >= value->len) {
                goto error;
            }

            if (!(value->data[i + 1] >= '0'&&value->data[i + 1] <= '9')) {
                goto error;
            }
        } else {
            goto error;
        }
    }

    version += ver * scale;
    if (op == NGX_HTTP_UA_MATCH_LE || op == NGX_HTTP_UA_MATCH_INTERVAL) {
        interval->right = version;

    } else if (op == NGX_HTTP_UA_MATCH_GE) {
        interval->left = version;

    } else if (op == NGX_HTTP_UA_MATCH_EXACT) {
        interval->left = version;
        interval->right = version;
    }

    return interval;

error:
    ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "invalid version");
    return NULL;
}