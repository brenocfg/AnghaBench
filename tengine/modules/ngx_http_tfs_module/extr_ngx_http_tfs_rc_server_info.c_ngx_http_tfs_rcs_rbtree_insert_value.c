#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ key; struct TYPE_9__* right; struct TYPE_9__* left; struct TYPE_9__* parent; int /*<<< orphan*/  color; } ;
typedef  TYPE_2__ ngx_rbtree_node_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {TYPE_1__ appkey; } ;
typedef  TYPE_3__ ngx_http_tfs_rcs_info_t ;

/* Variables and functions */
 scalar_t__ ngx_memn2cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rbt_red (TYPE_2__*) ; 

__attribute__((used)) static void
ngx_http_tfs_rcs_rbtree_insert_value(ngx_rbtree_node_t *temp,
    ngx_rbtree_node_t *node, ngx_rbtree_node_t *sentinel)
{
    ngx_int_t                 rc;
    ngx_rbtree_node_t       **p;
    ngx_http_tfs_rcs_info_t  *trn, *trnt;

    for ( ;; ) {

        if (node->key < temp->key) {

            p = &temp->left;

        } else if (node->key > temp->key) {

            p = &temp->right;

        } else { /* node->key == temp->key */

            trn = (ngx_http_tfs_rcs_info_t *) &node->color;
            trnt = (ngx_http_tfs_rcs_info_t *) &temp->color;

            rc = ngx_memn2cmp(trn->appkey.data, trnt->appkey.data,
                              trn->appkey.len, trn->appkey.len);
            if (rc < 0) {
                p = &temp->left;

            } else if (rc > 0) {
                p = &temp->right;

            } else {
                return;
            }
        }

        if (*p == sentinel) {
            break;
        }

        temp = *p;
    }

    *p = node;
    node->parent = temp;
    node->left = sentinel;
    node->right = sentinel;
    ngx_rbt_red(node);
}