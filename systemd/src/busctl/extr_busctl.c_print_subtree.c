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

/* Variables and functions */
 int /*<<< orphan*/  SPECIAL_GLYPH_TREE_BRANCH ; 
 int /*<<< orphan*/  SPECIAL_GLYPH_TREE_RIGHT ; 
 int /*<<< orphan*/  SPECIAL_GLYPH_TREE_SPACE ; 
 int /*<<< orphan*/  SPECIAL_GLYPH_TREE_VERTICAL ; 
 int /*<<< orphan*/  path_startswith (char*,char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*,char*,char*) ; 
 char* special_glyph (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  streq (char*,char const*) ; 
 char* strjoina (char const*,char*) ; 

__attribute__((used)) static void print_subtree(const char *prefix, const char *path, char **l) {
        const char *vertical, *space;
        char **n;

        /* We assume the list is sorted. Let's first skip over the
         * entry we are looking at. */
        for (;;) {
                if (!*l)
                        return;

                if (!streq(*l, path))
                        break;

                l++;
        }

        vertical = strjoina(prefix, special_glyph(SPECIAL_GLYPH_TREE_VERTICAL));
        space = strjoina(prefix, special_glyph(SPECIAL_GLYPH_TREE_SPACE));

        for (;;) {
                bool has_more = false;

                if (!*l || !path_startswith(*l, path))
                        break;

                n = l + 1;
                for (;;) {
                        if (!*n || !path_startswith(*n, path))
                                break;

                        if (!path_startswith(*n, *l)) {
                                has_more = true;
                                break;
                        }

                        n++;
                }

                printf("%s%s%s\n", prefix, special_glyph(has_more ? SPECIAL_GLYPH_TREE_BRANCH : SPECIAL_GLYPH_TREE_RIGHT), *l);

                print_subtree(has_more ? vertical : space, *l, l);
                l = n;
        }
}