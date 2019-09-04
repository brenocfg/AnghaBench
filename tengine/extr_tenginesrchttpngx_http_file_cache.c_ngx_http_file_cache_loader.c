#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  log; scalar_t__ alloc; TYPE_4__* data; int /*<<< orphan*/  spec_handler; int /*<<< orphan*/  post_tree_handler; int /*<<< orphan*/  pre_tree_handler; int /*<<< orphan*/  file_handler; int /*<<< orphan*/ * init_handler; } ;
typedef  TYPE_3__ ngx_tree_ctx_t ;
struct TYPE_10__ {double bsize; TYPE_2__* sh; TYPE_1__* path; scalar_t__ files; int /*<<< orphan*/  last; } ;
typedef  TYPE_4__ ngx_http_file_cache_t ;
struct TYPE_11__ {int /*<<< orphan*/  log; } ;
struct TYPE_8__ {scalar_t__ size; scalar_t__ loading; scalar_t__ cold; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ NGX_ABORT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_NOTICE ; 
 int /*<<< orphan*/  ngx_atomic_cmp_set (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_current_msec ; 
 TYPE_6__* ngx_cycle ; 
 int /*<<< orphan*/  ngx_http_file_cache_delete_file ; 
 int /*<<< orphan*/  ngx_http_file_cache_manage_directory ; 
 int /*<<< orphan*/  ngx_http_file_cache_manage_file ; 
 int /*<<< orphan*/  ngx_http_file_cache_noop ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/  ngx_pid ; 
 scalar_t__ ngx_walk_tree (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ngx_http_file_cache_loader(void *data)
{
    ngx_http_file_cache_t  *cache = data;

    ngx_tree_ctx_t  tree;

    if (!cache->sh->cold || cache->sh->loading) {
        return;
    }

    if (!ngx_atomic_cmp_set(&cache->sh->loading, 0, ngx_pid)) {
        return;
    }

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, ngx_cycle->log, 0,
                   "http file cache loader");

    tree.init_handler = NULL;
    tree.file_handler = ngx_http_file_cache_manage_file;
    tree.pre_tree_handler = ngx_http_file_cache_manage_directory;
    tree.post_tree_handler = ngx_http_file_cache_noop;
    tree.spec_handler = ngx_http_file_cache_delete_file;
    tree.data = cache;
    tree.alloc = 0;
    tree.log = ngx_cycle->log;

    cache->last = ngx_current_msec;
    cache->files = 0;

    if (ngx_walk_tree(&tree, &cache->path->name) == NGX_ABORT) {
        cache->sh->loading = 0;
        return;
    }

    cache->sh->cold = 0;
    cache->sh->loading = 0;

    ngx_log_error(NGX_LOG_NOTICE, ngx_cycle->log, 0,
                  "http file cache: %V %.3fM, bsize: %uz",
                  &cache->path->name,
                  ((double) cache->sh->size * cache->bsize) / (1024 * 1024),
                  cache->bsize);
}