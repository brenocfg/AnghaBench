#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct trie_node_f {int /*<<< orphan*/  children_count; } ;
struct trie_child_entry_f {int /*<<< orphan*/  child_off; int /*<<< orphan*/  c; } ;
struct TYPE_6__ {TYPE_1__* head; } ;
typedef  TYPE_2__ sd_hwdb ;
struct TYPE_5__ {int /*<<< orphan*/  child_entry_size; int /*<<< orphan*/  node_size; } ;

/* Variables and functions */
 struct trie_child_entry_f* bsearch (struct trie_child_entry_f*,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int le64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trie_children_cmp_f ; 
 struct trie_node_f const* trie_node_from_off (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct trie_node_f *node_lookup_f(sd_hwdb *hwdb, const struct trie_node_f *node, uint8_t c) {
        struct trie_child_entry_f *child;
        struct trie_child_entry_f search;

        search.c = c;
        child = bsearch(&search, (const char *)node + le64toh(hwdb->head->node_size), node->children_count,
                        le64toh(hwdb->head->child_entry_size), trie_children_cmp_f);
        if (child)
                return trie_node_from_off(hwdb, child->child_off);
        return NULL;
}