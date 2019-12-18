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
struct trie_node_f {size_t children_count; int /*<<< orphan*/  values_count; int /*<<< orphan*/  prefix_off; } ;
struct trie_child_entry_f {int /*<<< orphan*/  child_off; int /*<<< orphan*/  c; } ;
struct linebuf {int dummy; } ;
typedef  int /*<<< orphan*/  sd_hwdb ;

/* Variables and functions */
 scalar_t__ fnmatch (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int hwdb_add_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t le64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linebuf_add (struct linebuf*,char const*,size_t) ; 
 int /*<<< orphan*/  linebuf_add_char (struct linebuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linebuf_get (struct linebuf*) ; 
 int /*<<< orphan*/  linebuf_rem (struct linebuf*,size_t) ; 
 int /*<<< orphan*/  linebuf_rem_char (struct linebuf*) ; 
 size_t strlen (char const*) ; 
 struct trie_child_entry_f* trie_node_child (int /*<<< orphan*/ *,struct trie_node_f const*,size_t) ; 
 struct trie_node_f* trie_node_from_off (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trie_node_value (int /*<<< orphan*/ *,struct trie_node_f const*,size_t) ; 
 char* trie_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int trie_fnmatch_f(sd_hwdb *hwdb, const struct trie_node_f *node, size_t p,
                          struct linebuf *buf, const char *search) {
        size_t len;
        size_t i;
        const char *prefix;
        int err;

        prefix = trie_string(hwdb, node->prefix_off);
        len = strlen(prefix + p);
        linebuf_add(buf, prefix + p, len);

        for (i = 0; i < node->children_count; i++) {
                const struct trie_child_entry_f *child = trie_node_child(hwdb, node, i);

                linebuf_add_char(buf, child->c);
                err = trie_fnmatch_f(hwdb, trie_node_from_off(hwdb, child->child_off), 0, buf, search);
                if (err < 0)
                        return err;
                linebuf_rem_char(buf);
        }

        if (le64toh(node->values_count) && fnmatch(linebuf_get(buf), search, 0) == 0)
                for (i = 0; i < le64toh(node->values_count); i++) {
                        err = hwdb_add_property(hwdb, trie_node_value(hwdb, node, i));
                        if (err < 0)
                                return err;
                }

        linebuf_rem(buf, len);
        return 0;
}