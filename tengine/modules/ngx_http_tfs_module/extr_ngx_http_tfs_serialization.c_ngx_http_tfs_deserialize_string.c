#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * ngx_pcalloc (int /*<<< orphan*/ *,scalar_t__) ; 

ngx_int_t
ngx_http_tfs_deserialize_string(u_char **p, ngx_pool_t *pool,
    ngx_str_t *string)
{
    if (p == NULL || *p == NULL || pool == NULL || string == NULL) {
        return NGX_ERROR;
    }

    string->len = *((uint32_t *)*p);
    (*p) += sizeof(uint32_t);

    if (string->len > 0) {
        /* this length includes '/0' */
        string->len -= 1;
        string->data = ngx_pcalloc(pool, string->len);
        if (string->data == NULL) {
            return NGX_ERROR;
        }
        ngx_memcpy(string->data, (*p), string->len);
        (*p) += string->len + 1;
    }

    return NGX_OK;
}