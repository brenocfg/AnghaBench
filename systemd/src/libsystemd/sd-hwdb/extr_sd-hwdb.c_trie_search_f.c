#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct trie_node_f {int /*<<< orphan*/  values_count; scalar_t__ prefix_off; } ;
struct linebuf {int dummy; } ;
struct TYPE_11__ {TYPE_1__* head; } ;
typedef  TYPE_2__ sd_hwdb ;
struct TYPE_10__ {int /*<<< orphan*/  nodes_root_off; } ;

/* Variables and functions */
 scalar_t__ IN_SET (char,char,char,char) ; 
 int hwdb_add_property (TYPE_2__*,int /*<<< orphan*/ ) ; 
 size_t le64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linebuf_add_char (struct linebuf*,char) ; 
 int /*<<< orphan*/  linebuf_init (struct linebuf*) ; 
 int /*<<< orphan*/  linebuf_rem_char (struct linebuf*) ; 
 struct trie_node_f* node_lookup_f (TYPE_2__*,struct trie_node_f const*,char const) ; 
 int trie_fnmatch_f (TYPE_2__*,struct trie_node_f const*,size_t,struct linebuf*,char const*) ; 
 struct trie_node_f* trie_node_from_off (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trie_node_value (TYPE_2__*,struct trie_node_f const*,size_t) ; 
 char* trie_string (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static int trie_search_f(sd_hwdb *hwdb, const char *search) {
        struct linebuf buf;
        const struct trie_node_f *node;
        size_t i = 0;
        int err;

        linebuf_init(&buf);

        node = trie_node_from_off(hwdb, hwdb->head->nodes_root_off);
        while (node) {
                const struct trie_node_f *child;
                size_t p = 0;

                if (node->prefix_off) {
                        char c;

                        for (; (c = trie_string(hwdb, node->prefix_off)[p]); p++) {
                                if (IN_SET(c, '*', '?', '['))
                                        return trie_fnmatch_f(hwdb, node, p, &buf, search + i + p);
                                if (c != search[i + p])
                                        return 0;
                        }
                        i += p;
                }

                child = node_lookup_f(hwdb, node, '*');
                if (child) {
                        linebuf_add_char(&buf, '*');
                        err = trie_fnmatch_f(hwdb, child, 0, &buf, search + i);
                        if (err < 0)
                                return err;
                        linebuf_rem_char(&buf);
                }

                child = node_lookup_f(hwdb, node, '?');
                if (child) {
                        linebuf_add_char(&buf, '?');
                        err = trie_fnmatch_f(hwdb, child, 0, &buf, search + i);
                        if (err < 0)
                                return err;
                        linebuf_rem_char(&buf);
                }

                child = node_lookup_f(hwdb, node, '[');
                if (child) {
                        linebuf_add_char(&buf, '[');
                        err = trie_fnmatch_f(hwdb, child, 0, &buf, search + i);
                        if (err < 0)
                                return err;
                        linebuf_rem_char(&buf);
                }

                if (search[i] == '\0') {
                        size_t n;

                        for (n = 0; n < le64toh(node->values_count); n++) {
                                err = hwdb_add_property(hwdb, trie_node_value(hwdb, node, n));
                                if (err < 0)
                                        return err;
                        }
                        return 0;
                }

                child = node_lookup_f(hwdb, node, search[i]);
                node = child;
                i++;
        }
        return 0;
}