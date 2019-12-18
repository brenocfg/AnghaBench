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
struct trie {int /*<<< orphan*/  strings; int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct trie*) ; 
 int /*<<< orphan*/  strbuf_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trie_node_cleanup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void trie_free(struct trie *trie) {
        if (!trie)
                return;

        trie_node_cleanup(trie->root);
        strbuf_cleanup(trie->strings);
        free(trie);
}