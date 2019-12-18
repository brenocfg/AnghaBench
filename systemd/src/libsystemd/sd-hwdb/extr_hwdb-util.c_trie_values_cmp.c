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
struct trie_value_entry {scalar_t__ key_off; } ;
struct trie {TYPE_1__* strings; } ;
struct TYPE_2__ {scalar_t__ buf; } ;

/* Variables and functions */
 int strcmp (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int trie_values_cmp(const struct trie_value_entry *a, const struct trie_value_entry *b, struct trie *trie) {
        return strcmp(trie->strings->buf + a->key_off,
                      trie->strings->buf + b->key_off);
}