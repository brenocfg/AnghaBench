#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
struct TYPE_11__ {int /*<<< orphan*/ * root; } ;
typedef  TYPE_2__ rtree_t ;
typedef  int /*<<< orphan*/  rtree_node_elm_t ;
typedef  int /*<<< orphan*/  rtree_leaf_elm_t ;
struct TYPE_12__ {TYPE_1__* cache; TYPE_8__* l2_cache; } ;
typedef  TYPE_3__ rtree_ctx_t ;
typedef  int /*<<< orphan*/  rtree_ctx_cache_elm_t ;
struct TYPE_13__ {uintptr_t leafkey; int /*<<< orphan*/ * leaf; } ;
struct TYPE_10__ {uintptr_t leafkey; int /*<<< orphan*/ * leaf; } ;

/* Variables and functions */
 unsigned int RTREE_CTX_NCACHE ; 
 unsigned int RTREE_CTX_NCACHE_L2 ; 
 int RTREE_HEIGHT ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ config_debug ; 
 int /*<<< orphan*/  memmove (TYPE_8__*,TYPE_8__*,int) ; 
 int /*<<< orphan*/  not_reached () ; 
 size_t rtree_cache_direct_map (uintptr_t) ; 
 int /*<<< orphan*/ * rtree_child_leaf_read (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,unsigned int,int) ; 
 int /*<<< orphan*/ * rtree_child_leaf_tryread (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * rtree_child_node_read (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,unsigned int,int) ; 
 int /*<<< orphan*/ * rtree_child_node_tryread (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtree_leaf_valid (int /*<<< orphan*/ *) ; 
 uintptr_t rtree_leafkey (uintptr_t) ; 
 int /*<<< orphan*/  rtree_node_valid (int /*<<< orphan*/ *) ; 
 uintptr_t rtree_subkey (uintptr_t,int) ; 
 scalar_t__ unlikely (int) ; 

rtree_leaf_elm_t *
rtree_leaf_elm_lookup_hard(tsdn_t *tsdn, rtree_t *rtree, rtree_ctx_t *rtree_ctx,
    uintptr_t key, bool dependent, bool init_missing) {
	rtree_node_elm_t *node;
	rtree_leaf_elm_t *leaf;
#if RTREE_HEIGHT > 1
	node = rtree->root;
#else
	leaf = rtree->root;
#endif

	if (config_debug) {
		uintptr_t leafkey = rtree_leafkey(key);
		for (unsigned i = 0; i < RTREE_CTX_NCACHE; i++) {
			assert(rtree_ctx->cache[i].leafkey != leafkey);
		}
		for (unsigned i = 0; i < RTREE_CTX_NCACHE_L2; i++) {
			assert(rtree_ctx->l2_cache[i].leafkey != leafkey);
		}
	}

#define RTREE_GET_CHILD(level) {					\
		assert(level < RTREE_HEIGHT-1);				\
		if (level != 0 && !dependent &&				\
		    unlikely(!rtree_node_valid(node))) {		\
			return NULL;					\
		}							\
		uintptr_t subkey = rtree_subkey(key, level);		\
		if (level + 2 < RTREE_HEIGHT) {				\
			node = init_missing ?				\
			    rtree_child_node_read(tsdn, rtree,		\
			    &node[subkey], level, dependent) :		\
			    rtree_child_node_tryread(&node[subkey],	\
			    dependent);					\
		} else {						\
			leaf = init_missing ?				\
			    rtree_child_leaf_read(tsdn, rtree,		\
			    &node[subkey], level, dependent) :		\
			    rtree_child_leaf_tryread(&node[subkey],	\
			    dependent);					\
		}							\
	}
	/*
	 * Cache replacement upon hard lookup (i.e. L1 & L2 rtree cache miss):
	 * (1) evict last entry in L2 cache; (2) move the collision slot from L1
	 * cache down to L2; and 3) fill L1.
	 */
#define RTREE_GET_LEAF(level) {						\
		assert(level == RTREE_HEIGHT-1);			\
		if (!dependent && unlikely(!rtree_leaf_valid(leaf))) {	\
			return NULL;					\
		}							\
		if (RTREE_CTX_NCACHE_L2 > 1) {				\
			memmove(&rtree_ctx->l2_cache[1],		\
			    &rtree_ctx->l2_cache[0],			\
			    sizeof(rtree_ctx_cache_elm_t) *		\
			    (RTREE_CTX_NCACHE_L2 - 1));			\
		}							\
		size_t slot = rtree_cache_direct_map(key);		\
		rtree_ctx->l2_cache[0].leafkey =			\
		    rtree_ctx->cache[slot].leafkey;			\
		rtree_ctx->l2_cache[0].leaf =				\
		    rtree_ctx->cache[slot].leaf;			\
		uintptr_t leafkey = rtree_leafkey(key);			\
		rtree_ctx->cache[slot].leafkey = leafkey;		\
		rtree_ctx->cache[slot].leaf = leaf;			\
		uintptr_t subkey = rtree_subkey(key, level);		\
		return &leaf[subkey];					\
	}
	if (RTREE_HEIGHT > 1) {
		RTREE_GET_CHILD(0)
	}
	if (RTREE_HEIGHT > 2) {
		RTREE_GET_CHILD(1)
	}
	if (RTREE_HEIGHT > 3) {
		for (unsigned i = 2; i < RTREE_HEIGHT-1; i++) {
			RTREE_GET_CHILD(i)
		}
	}
	RTREE_GET_LEAF(RTREE_HEIGHT-1)
#undef RTREE_GET_CHILD
#undef RTREE_GET_LEAF
	not_reached();
}