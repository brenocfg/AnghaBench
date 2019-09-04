#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_8__ {size_t min_match_len; size_t max_match_len; size_t* shift; size_t* index; } ;
typedef  TYPE_2__ ngx_http_sub_tables_t ;
struct TYPE_7__ {size_t len; size_t* data; } ;
struct TYPE_9__ {TYPE_1__ match; } ;
typedef  TYPE_3__ ngx_http_sub_match_t ;

/* Variables and functions */
 int ngx_http_sub_cmp_index ; 
 int /*<<< orphan*/  ngx_http_sub_cmp_matches ; 
 size_t ngx_max (size_t,size_t) ; 
 int /*<<< orphan*/  ngx_memset (size_t*,size_t,int) ; 
 void* ngx_min (size_t,size_t) ; 
 int /*<<< orphan*/  ngx_sort (TYPE_3__*,size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_http_sub_init_tables(ngx_http_sub_tables_t *tables,
    ngx_http_sub_match_t *match, ngx_uint_t n)
{
    u_char      c;
    ngx_uint_t  i, j, min, max, ch;

    min = match[0].match.len;
    max = match[0].match.len;

    for (i = 1; i < n; i++) {
        min = ngx_min(min, match[i].match.len);
        max = ngx_max(max, match[i].match.len);
    }

    tables->min_match_len = min;
    tables->max_match_len = max;

    ngx_http_sub_cmp_index = tables->min_match_len - 1;
    ngx_sort(match, n, sizeof(ngx_http_sub_match_t), ngx_http_sub_cmp_matches);

    min = ngx_min(min, 255);
    ngx_memset(tables->shift, min, 256);

    ch = 0;

    for (i = 0; i < n; i++) {

        for (j = 0; j < min; j++) {
            c = match[i].match.data[tables->min_match_len - 1 - j];
            tables->shift[c] = ngx_min(tables->shift[c], (u_char) j);
        }

        c = match[i].match.data[tables->min_match_len - 1];
        while (ch <= (ngx_uint_t) c) {
            tables->index[ch++] = (u_char) i;
        }
    }

    while (ch < 257) {
        tables->index[ch++] = (u_char) n;
    }
}