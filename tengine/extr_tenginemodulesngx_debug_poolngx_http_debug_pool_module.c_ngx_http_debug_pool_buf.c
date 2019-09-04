#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
struct TYPE_5__ {size_t size; size_t cnum; size_t lnum; size_t func; int /*<<< orphan*/ * num; struct TYPE_5__* next; } ;
typedef  TYPE_1__ ngx_pool_stat_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_6__ {int memory; int last_buf; int /*<<< orphan*/ * last; int /*<<< orphan*/ * pos; } ;
typedef  TYPE_2__ ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 size_t NGX_POOL_STATS_MAX ; 
 int NGX_TIME_T_LEN ; 
 int /*<<< orphan*/ * ngx_palloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ngx_pid ; 
 TYPE_1__** ngx_pool_stats ; 
 int ngx_pool_stats_num ; 
 int /*<<< orphan*/ * ngx_snprintf (int /*<<< orphan*/ *,int,char*,size_t,int /*<<< orphan*/ *,size_t,size_t,size_t) ; 
 int /*<<< orphan*/ * ngx_sprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_debug_pool_buf(ngx_pool_t *pool, ngx_buf_t *b)
{
    u_char              *p, *unit;
    size_t               size, s, n, cn, ln;
    ngx_uint_t           i;
    ngx_pool_stat_t     *stat;

#define NGX_POOL_PID_SIZE       (NGX_TIME_T_LEN + sizeof("pid:\n") - 1)     /* sizeof pid_t equals time_t */
#define NGX_POOL_PID_FORMAT     "pid:%P\n"
#define NGX_POOL_ENTRY_SIZE     (48 /* func */ + 12 * 4 + sizeof("size: num: cnum: lnum: \n") - 1)
#define NGX_POOL_ENTRY_FORMAT   "size:%12z num:%12z cnum:%12z lnum:%12z %s\n"
#define NGX_POOL_SUMMARY_SIZE   (12 * 4 + sizeof("size: num: cnum: lnum: [SUMMARY]\n") - 1)
#define NGX_POOL_SUMMARY_FORMAT "size:%10z%2s num:%12z cnum:%12z lnum:%12z [SUMMARY]\n"

    size = NGX_POOL_PID_SIZE + ngx_pool_stats_num * NGX_POOL_ENTRY_SIZE
           + NGX_POOL_SUMMARY_SIZE;
    p = ngx_palloc(pool, size);
    if (p == NULL) {
        return NGX_ERROR;
    }

    b->pos = p;

    p = ngx_sprintf(p, NGX_POOL_PID_FORMAT, ngx_pid);

    /* lines of entry */

    s = n = cn = ln = 0;

    for (i = 0; i < NGX_POOL_STATS_MAX; i++) {
        for (stat = ngx_pool_stats[i]; stat != NULL; stat = stat->next) {
            p = ngx_snprintf(p, NGX_POOL_ENTRY_SIZE, NGX_POOL_ENTRY_FORMAT,
                             stat->size, stat->num, stat->cnum, stat->lnum,
                             stat->func);
            s += stat->size;
            n += stat->num;
            cn += stat->cnum;
            ln += stat->lnum;
        }
    }

    /* summary line */

    unit = (u_char *) " B";

    if (s > 1024 * 1024) {
        s = s / (1024 * 1024);
        unit = (u_char *) "MB";
    } else if (s > 1024) {
        s = s / 1024;
        unit = (u_char *) "KB";
    }

    p = ngx_snprintf(p, NGX_POOL_SUMMARY_SIZE, NGX_POOL_SUMMARY_FORMAT,
                     s, unit, n, cn, ln);

    b->last = p;
    b->memory = 1;
    b->last_buf = 1;

    return NGX_OK;
}