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
struct trie_child_entry_f {int c; } ;

/* Variables and functions */

__attribute__((used)) static int trie_children_cmp_f(const void *v1, const void *v2) {
        const struct trie_child_entry_f *n1 = v1;
        const struct trie_child_entry_f *n2 = v2;

        return n1->c - n2->c;
}