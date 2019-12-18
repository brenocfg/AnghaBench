#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_3__ {scalar_t__* data; } ;
struct TYPE_4__ {TYPE_1__ match; } ;
typedef  TYPE_2__ ngx_http_sub_match_t ;

/* Variables and functions */
 size_t ngx_http_sub_cmp_index ; 

__attribute__((used)) static ngx_int_t
ngx_http_sub_cmp_matches(const void *one, const void *two)
{
    ngx_int_t              c1, c2;
    ngx_http_sub_match_t  *first, *second;

    first = (ngx_http_sub_match_t *) one;
    second = (ngx_http_sub_match_t *) two;

    c1 = first->match.data[ngx_http_sub_cmp_index];
    c2 = second->match.data[ngx_http_sub_cmp_index];

    return c1 - c2;
}