#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rbnode {int dummy; } ;
struct msg {int dummy; } ;

/* Variables and functions */
 struct msg* msg_from_rbe (struct rbnode*) ; 
 struct rbnode* rbtree_min (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmo_rbt ; 

struct msg *
msg_tmo_min(void)
{
    struct rbnode *node;

    node = rbtree_min(&tmo_rbt);
    if (node == NULL) {
        return NULL;
    }

    return msg_from_rbe(node);
}