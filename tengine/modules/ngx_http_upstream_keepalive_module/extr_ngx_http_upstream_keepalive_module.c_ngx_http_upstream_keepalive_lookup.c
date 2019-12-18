#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ key; struct TYPE_12__* right; struct TYPE_12__* left; int /*<<< orphan*/  color; } ;
typedef  TYPE_4__ ngx_rbtree_node_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_11__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_13__ {scalar_t__ hash; TYPE_3__ key; TYPE_2__* conf; } ;
typedef  TYPE_5__ ngx_http_upstream_keepalive_peer_data_t ;
struct TYPE_14__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_6__ ngx_http_upstream_keepalive_node_t ;
struct TYPE_10__ {TYPE_1__* index; } ;
struct TYPE_9__ {TYPE_4__* sentinel; TYPE_4__* root; } ;

/* Variables and functions */
 scalar_t__ ngx_memn2cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_http_upstream_keepalive_node_t *
ngx_http_upstream_keepalive_lookup(ngx_http_upstream_keepalive_peer_data_t *kp)
{
    ngx_int_t                            rc;
    ngx_rbtree_node_t                   *node, *sentinel;
    ngx_http_upstream_keepalive_node_t  *ukn;

    node = kp->conf->index->root;
    sentinel = kp->conf->index->sentinel;

    while (node != sentinel) {

        if (kp->hash < node->key) {
            node = node->left;
            continue;
        }

        if (kp->hash > node->key) {
            node = node->right;
            continue;
        }

        /* hash == node->key */

        ukn = (ngx_http_upstream_keepalive_node_t *) &node->color;

        rc = ngx_memn2cmp(kp->key.data, ukn->data, kp->key.len, ukn->len);

        if (rc == 0) {
            return ukn;
        }

        node = (rc < 0) ? node->left : node->right;
    }

    return NULL;
}