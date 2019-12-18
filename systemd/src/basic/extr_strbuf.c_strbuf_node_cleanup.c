#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strbuf_node {size_t children_count; TYPE_1__* children; } ;
struct TYPE_2__ {struct strbuf_node* child; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 struct strbuf_node* mfree (struct strbuf_node*) ; 

__attribute__((used)) static struct strbuf_node* strbuf_node_cleanup(struct strbuf_node *node) {
        size_t i;

        for (i = 0; i < node->children_count; i++)
                strbuf_node_cleanup(node->children[i].child);
        free(node->children);
        return mfree(node);
}