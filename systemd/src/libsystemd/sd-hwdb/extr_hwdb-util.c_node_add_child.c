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
struct trie_node {int children_count; struct trie_child_entry* children; } ;
struct trie_child_entry {struct trie_node* child; int /*<<< orphan*/  c; } ;
struct trie {int /*<<< orphan*/  nodes_count; int /*<<< orphan*/  children_count; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct trie_child_entry* reallocarray (struct trie_child_entry*,int,int) ; 
 int /*<<< orphan*/  trie_children_cmp ; 
 int /*<<< orphan*/  typesafe_qsort (struct trie_child_entry*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int node_add_child(struct trie *trie, struct trie_node *node, struct trie_node *node_child, uint8_t c) {
        struct trie_child_entry *child;

        /* extend array, add new entry, sort for bisection */
        child = reallocarray(node->children, node->children_count + 1, sizeof(struct trie_child_entry));
        if (!child)
                return -ENOMEM;

        node->children = child;
        trie->children_count++;
        node->children[node->children_count].c = c;
        node->children[node->children_count].child = node_child;
        node->children_count++;
        typesafe_qsort(node->children, node->children_count, trie_children_cmp);
        trie->nodes_count++;

        return 0;
}