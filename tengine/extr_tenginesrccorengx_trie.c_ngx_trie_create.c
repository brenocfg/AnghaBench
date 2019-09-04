#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  build_clue; int /*<<< orphan*/  query; int /*<<< orphan*/  insert; int /*<<< orphan*/ * pool; int /*<<< orphan*/ * root; } ;
typedef  TYPE_1__ ngx_trie_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;

/* Variables and functions */
 TYPE_1__* ngx_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_trie_build_clue ; 
 int /*<<< orphan*/  ngx_trie_insert ; 
 int /*<<< orphan*/ * ngx_trie_node_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_trie_query ; 

ngx_trie_t *
ngx_trie_create(ngx_pool_t *pool)
{
    ngx_trie_t *trie;

    trie = ngx_palloc(pool, sizeof(ngx_trie_t));
    if (trie == NULL) {
        return NULL;
    }

    trie->root = ngx_trie_node_create(pool);
    if (trie->root == NULL) {
        return NULL;
    }

    trie->pool = pool;
    trie->insert = ngx_trie_insert;
    trie->query = ngx_trie_query;
    trie->build_clue = ngx_trie_build_clue;

    return trie;
}