#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct trie_node_f {int dummy; } ;
struct trie_child_entry_f {int dummy; } ;
struct TYPE_5__ {TYPE_1__* head; } ;
typedef  TYPE_2__ sd_hwdb ;
struct TYPE_4__ {int /*<<< orphan*/  child_entry_size; int /*<<< orphan*/  node_size; } ;

/* Variables and functions */
 size_t le64toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct trie_child_entry_f *trie_node_child(sd_hwdb *hwdb, const struct trie_node_f *node, size_t idx) {
        const char *base = (const char *)node;

        base += le64toh(hwdb->head->node_size);
        base += idx * le64toh(hwdb->head->child_entry_size);
        return (const struct trie_child_entry_f *)base;
}