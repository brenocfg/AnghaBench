#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
typedef  scalar_t__ ngx_int_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_tfs_deserialize_string (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_memzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ngx_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ngx_prealloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

ngx_int_t
ngx_http_tfs_deserialize_vstring(u_char **p, ngx_pool_t *pool,
    uint32_t *count, ngx_str_t **string)
{
    uint32_t   new_count, i;
    ngx_int_t  rc;

    /* count */
    new_count = *((uint32_t *)*p);
    (*p) += sizeof(uint32_t);

    /* string */
    if (new_count > 0) {
        if (*string == NULL) {
            *string = ngx_pcalloc(pool, sizeof(ngx_str_t) * new_count);
            if (*string == NULL) {
                return NGX_ERROR;
            }

        } else if (new_count > *count) {
            *string = ngx_prealloc(pool, *string, sizeof(ngx_str_t) * (*count),
                                   sizeof(ngx_str_t) * new_count);
            if (*string == NULL) {
                return NGX_ERROR;
            }
            ngx_memzero(*string, sizeof(ngx_str_t) * new_count);
        }
        for (i = 0; i < new_count; i++) {
            rc = ngx_http_tfs_deserialize_string(p, pool, (*string) + i);
            if (rc == NGX_ERROR) {
                return NGX_ERROR;
            }
        }
    }
    *count = new_count;

    return NGX_OK;
}