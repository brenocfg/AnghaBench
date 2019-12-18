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
typedef  int /*<<< orphan*/  uint8_t ;
struct strbuf_node {int children_count; struct strbuf_child_entry* children; } ;
struct strbuf_child_entry {struct strbuf_node* child; int /*<<< orphan*/  c; } ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (struct strbuf_child_entry*,struct strbuf_child_entry*,int) ; 
 scalar_t__ strbuf_children_cmp (struct strbuf_child_entry*,struct strbuf_child_entry*) ; 

__attribute__((used)) static void bubbleinsert(struct strbuf_node *node,
                         uint8_t c,
                         struct strbuf_node *node_child) {

        struct strbuf_child_entry new = {
                .c = c,
                .child = node_child,
        };
        int left = 0, right = node->children_count;

        while (right > left) {
                int middle = (right + left) / 2 ;
                if (strbuf_children_cmp(&node->children[middle], &new) <= 0)
                        left = middle + 1;
                else
                        right = middle;
        }

        memmove(node->children + left + 1, node->children + left,
                sizeof(struct strbuf_child_entry) * (node->children_count - left));
        node->children[left] = new;

        node->children_count++;
}