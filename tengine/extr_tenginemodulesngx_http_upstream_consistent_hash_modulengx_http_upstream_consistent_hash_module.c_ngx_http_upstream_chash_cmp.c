#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_2__ {scalar_t__ hash; } ;
typedef  TYPE_1__ ngx_http_upstream_chash_server_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_CHASH_EQUAL ; 
 int /*<<< orphan*/  NGX_CHASH_GREAT ; 
 int /*<<< orphan*/  NGX_CHASH_LESS ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_chash_cmp(const void *one, const void *two)
{
    ngx_http_upstream_chash_server_t *frist, *second;

    frist = (ngx_http_upstream_chash_server_t *)one;
    second = (ngx_http_upstream_chash_server_t *) two;

    if (frist->hash > second->hash) {
        return NGX_CHASH_GREAT;

    } else if (frist->hash == second->hash) {
        return NGX_CHASH_EQUAL;

    } else {
        return NGX_CHASH_LESS;
    }
}