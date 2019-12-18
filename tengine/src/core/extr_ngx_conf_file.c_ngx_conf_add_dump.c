#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ off_t ;
struct TYPE_22__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_5__ ngx_str_t ;
struct TYPE_17__ {int /*<<< orphan*/  key; } ;
struct TYPE_20__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
struct TYPE_23__ {TYPE_11__ node; TYPE_3__ str; } ;
typedef  TYPE_6__ ngx_str_node_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_24__ {TYPE_4__* cycle; int /*<<< orphan*/  temp_pool; TYPE_2__* conf_file; } ;
typedef  TYPE_7__ ngx_conf_t ;
struct TYPE_25__ {TYPE_3__ name; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_8__ ngx_conf_dump_t ;
typedef  int /*<<< orphan*/  ngx_buf_t ;
struct TYPE_21__ {int /*<<< orphan*/  config_dump_rbtree; int /*<<< orphan*/  pool; int /*<<< orphan*/  config_dump; } ;
struct TYPE_18__ {int /*<<< orphan*/  info; } ;
struct TYPE_19__ {int /*<<< orphan*/ * dump; TYPE_1__ file; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_8__* ngx_array_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_crc32_long (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_create_temp_buf (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ ngx_file_size (int /*<<< orphan*/ *) ; 
 TYPE_6__* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ngx_pstrdup (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_rbtree_insert (int /*<<< orphan*/ *,TYPE_11__*) ; 
 TYPE_6__* ngx_str_rbtree_lookup (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_conf_add_dump(ngx_conf_t *cf, ngx_str_t *filename)
{
    off_t             size;
    u_char           *p;
    uint32_t          hash;
    ngx_buf_t        *buf;
    ngx_str_node_t   *sn;
    ngx_conf_dump_t  *cd;

    hash = ngx_crc32_long(filename->data, filename->len);

    sn = ngx_str_rbtree_lookup(&cf->cycle->config_dump_rbtree, filename, hash);

    if (sn) {
        cf->conf_file->dump = NULL;
        return NGX_OK;
    }

    p = ngx_pstrdup(cf->cycle->pool, filename);
    if (p == NULL) {
        return NGX_ERROR;
    }

    cd = ngx_array_push(&cf->cycle->config_dump);
    if (cd == NULL) {
        return NGX_ERROR;
    }

    size = ngx_file_size(&cf->conf_file->file.info);

    buf = ngx_create_temp_buf(cf->cycle->pool, (size_t) size);
    if (buf == NULL) {
        return NGX_ERROR;
    }

    cd->name.data = p;
    cd->name.len = filename->len;
    cd->buffer = buf;

    cf->conf_file->dump = buf;

    sn = ngx_palloc(cf->temp_pool, sizeof(ngx_str_node_t));
    if (sn == NULL) {
        return NGX_ERROR;
    }

    sn->node.key = hash;
    sn->str = cd->name;

    ngx_rbtree_insert(&cf->cycle->config_dump_rbtree, &sn->node);

    return NGX_OK;
}