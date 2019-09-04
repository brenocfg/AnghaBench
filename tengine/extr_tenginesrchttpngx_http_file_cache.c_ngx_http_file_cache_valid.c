#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
typedef  size_t ngx_uint_t ;
struct TYPE_4__ {scalar_t__ status; int /*<<< orphan*/  valid; } ;
typedef  TYPE_1__ ngx_http_cache_valid_t ;
struct TYPE_5__ {size_t nelts; TYPE_1__* elts; } ;
typedef  TYPE_2__ ngx_array_t ;

/* Variables and functions */

time_t
ngx_http_file_cache_valid(ngx_array_t *cache_valid, ngx_uint_t status)
{
    ngx_uint_t               i;
    ngx_http_cache_valid_t  *valid;

    if (cache_valid == NULL) {
        return 0;
    }

    valid = cache_valid->elts;
    for (i = 0; i < cache_valid->nelts; i++) {

        if (valid[i].status == 0) {
            return valid[i].valid;
        }

        if (valid[i].status == status) {
            return valid[i].valid;
        }
    }

    return 0;
}