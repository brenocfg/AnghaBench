#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_4__ {int len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
typedef  int /*<<< orphan*/  ngx_array_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ngx_array_create (int /*<<< orphan*/ *,int,int) ; 
 TYPE_1__* ngx_array_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_strlchr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char) ; 

ngx_array_t *
ngx_dyups_parse_path(ngx_pool_t *pool, ngx_str_t *path)
{
    u_char       *p, *last, *end;
    ngx_str_t    *str;
    ngx_array_t  *array;

    array = ngx_array_create(pool, 8, sizeof(ngx_str_t));
    if (array == NULL) {
        return NULL;
    }

    p = path->data + 1;
    last = path->data + path->len;

    while(p < last) {
        end = ngx_strlchr(p, last, '/');
        str = ngx_array_push(array);

        if (str == NULL) {
            return NULL;
        }

        if (end) {
            str->data = p;
            str->len = end - p;

        } else {
            str->data = p;
            str->len = last - p;

        }

        p += str->len + 1;
    }

#if (NGX_DEBUG)
    ngx_str_t  *arg;
    ngx_uint_t  i;

    arg = array->elts;
    for (i = 0; i < array->nelts; i++) {
        ngx_log_debug2(NGX_LOG_DEBUG_HTTP, ngx_cycle->log, 0,
                       "[dyups] res[%i]:%V", i, &arg[i]);
    }
#endif

    return array;
}