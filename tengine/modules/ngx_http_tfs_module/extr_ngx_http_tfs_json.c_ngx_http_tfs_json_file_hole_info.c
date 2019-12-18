#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yajl_gen ;
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_11__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  gen; } ;
typedef  TYPE_1__ ngx_http_tfs_json_gen_t ;
struct TYPE_12__ {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
typedef  TYPE_2__ ngx_http_tfs_file_hole_info_t ;
struct TYPE_13__ {TYPE_4__* buf; int /*<<< orphan*/ * next; } ;
typedef  TYPE_3__ ngx_chain_t ;
struct TYPE_14__ {int temporary; int flush; scalar_t__ last; scalar_t__ end; scalar_t__ pos; } ;
typedef  TYPE_4__ ngx_buf_t ;
struct TYPE_15__ {scalar_t__ nelts; scalar_t__ elts; } ;
typedef  TYPE_5__ ngx_array_t ;

/* Variables and functions */
 TYPE_3__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 TYPE_4__* ngx_calloc_buf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yajl_gen_array_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yajl_gen_array_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yajl_gen_get_buf (int /*<<< orphan*/ ,unsigned char const**,size_t*) ; 
 int /*<<< orphan*/  yajl_gen_integer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yajl_gen_map_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yajl_gen_map_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yajl_gen_string (int /*<<< orphan*/ ,unsigned char const*,int) ; 

ngx_chain_t *
ngx_http_tfs_json_file_hole_info(ngx_http_tfs_json_gen_t *tj_gen,
    ngx_array_t *file_holes)
{
    size_t                          size;
    yajl_gen                        g;
    ngx_buf_t                      *b;
    ngx_uint_t                      i;
    ngx_chain_t                    *cl;
    ngx_http_tfs_file_hole_info_t  *file_hole_info;

    g = tj_gen->gen;
    size = 0;

    yajl_gen_array_open(g);

    file_hole_info = (ngx_http_tfs_file_hole_info_t *) file_holes->elts;
    for(i = 0; i < file_holes->nelts; i++, file_hole_info++) {
        yajl_gen_map_open(g);

        yajl_gen_string(g, (const unsigned char *) "OFFSET", 6);
        yajl_gen_integer(g, file_hole_info->offset);

        yajl_gen_string(g, (const unsigned char *) "LENGTH", 6);
        yajl_gen_integer(g, file_hole_info->length);

        yajl_gen_map_close(g);
    }

    yajl_gen_array_close(g);

    cl = ngx_alloc_chain_link(tj_gen->pool);
    if (cl == NULL) {
        return NULL;
    }
    cl->next = NULL;

    b = ngx_calloc_buf(tj_gen->pool);
    if (b == NULL) {
        return NULL;
    }

    yajl_gen_get_buf(g, (const unsigned char **) &b->pos, &size);
    b->last = b->pos + size;
    b->end = b->last;
    b->temporary = 1;
    b->flush = 1;
    /* b->last_buf = 1; */
    cl->buf = b;
    return cl;
}