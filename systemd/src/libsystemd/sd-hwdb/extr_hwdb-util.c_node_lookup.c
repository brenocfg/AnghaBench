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
struct trie_node {int /*<<< orphan*/  children_count; int /*<<< orphan*/  children; } ;
struct trie_child_entry {struct trie_node* child; int /*<<< orphan*/  c; } ;

/* Variables and functions */
 int /*<<< orphan*/  trie_children_cmp ; 
 struct trie_child_entry* typesafe_bsearch (struct trie_child_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct trie_node *node_lookup(const struct trie_node *node, uint8_t c) {
        struct trie_child_entry *child;
        struct trie_child_entry search;

        search.c = c;
        child = typesafe_bsearch(&search, node->children, node->children_count, trie_children_cmp);
        if (child)
                return child->child;
        return NULL;
}