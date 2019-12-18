#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_15__ {TYPE_8__* (* query ) (TYPE_3__*,TYPE_4__*,size_t*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ ngx_trie_t ;
struct TYPE_16__ {char* data; scalar_t__ len; } ;
typedef  TYPE_4__ ngx_str_t ;
typedef  size_t ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_variable_value_t ;
struct TYPE_17__ {int left; int right; int /*<<< orphan*/ * var; } ;
typedef  TYPE_5__ ngx_http_user_agent_interval_t ;
struct TYPE_18__ {int /*<<< orphan*/ * default_value; TYPE_3__* trie; } ;
typedef  TYPE_6__ ngx_http_user_agent_ctx_t ;
struct TYPE_14__ {TYPE_1__* user_agent; } ;
struct TYPE_19__ {TYPE_2__ headers_in; } ;
typedef  TYPE_7__ ngx_http_request_t ;
struct TYPE_20__ {size_t nelts; TYPE_5__* elts; } ;
typedef  TYPE_8__ ngx_array_t ;
struct TYPE_13__ {TYPE_4__ value; } ;

/* Variables and functions */
 int NGX_HTTP_UA_MAX_INT64 ; 
 size_t NGX_HTTP_UA_MAX_OFFSET ; 
 size_t NGX_OK ; 
 int /*<<< orphan*/  NGX_TRIE_REVERSE ; 
 TYPE_8__* stub1 (TYPE_3__*,TYPE_4__*,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_user_agent_variable(ngx_http_request_t *r,
    ngx_http_variable_value_t *v, uintptr_t data)
{
    uint64_t                        ver, scale, version;
    ngx_int_t                       i, n, pos, offset;
    ngx_str_t                      *user_agent;
    ngx_trie_t                     *trie;
    ngx_array_t                    *value;
    ngx_http_user_agent_ctx_t      *uacf;
    ngx_http_user_agent_interval_t *array;

    uacf = (ngx_http_user_agent_ctx_t *) data;
    trie = uacf->trie;

    if (r->headers_in.user_agent == NULL) {
      goto end;
    }

    user_agent = &(r->headers_in.user_agent->value);

    value = trie->query(trie, user_agent, &pos, NGX_TRIE_REVERSE);
    if (value == NULL || pos < 0) {
        goto end;
    }

    version = 0;
    scale = NGX_HTTP_UA_MAX_INT64;
    ver = 0;
    offset = 0;

    for (/* void */; pos < (ngx_int_t) user_agent->len; pos++, offset++) {
        if (user_agent->data[pos] >= '0'
            && user_agent->data[pos] <= '9') {
            break;

        } else if (user_agent->data[pos] == ';'
                   || user_agent->data[pos] == '('
                   || user_agent->data[pos] == ')')
        {
            break;
        }

        if(offset >= NGX_HTTP_UA_MAX_OFFSET) {
            break;
        }
    }

    array = value->elts;
    n = value->nelts;

    for (/* void */ ; pos < (ngx_int_t) user_agent->len; pos++) {

        if (user_agent->data[pos] == '.') {
            version += ver * scale;
            ver = 0;
            scale /= 10000;
            continue;

        } else if(user_agent->data[pos] >= '0'
                  && user_agent->data[pos] <= '9') {

            ver = ver * 10 +user_agent->data[pos] - '0';
            continue;
        }

        break;
    }

    version += ver * scale;
    for (i = 0; i < n; i++) {
        if (version >= array[i].left && version <= array[i].right) {
            *v = *(array[i].var);
            return NGX_OK;
        }
    }

end:

    *v = *uacf->default_value;
    return NGX_OK;
}