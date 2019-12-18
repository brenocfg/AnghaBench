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
 int /*<<< orphan*/  assert (char const*) ; 
 scalar_t__ image_name_is_valid (char const*) ; 
 char* last_path_component (char const*) ; 
 scalar_t__ memcmp (char const*,char const*,size_t) ; 
 char* startswith (char const*,char const*) ; 
 size_t strcspn (char const*,char*) ; 
 scalar_t__ streq (char const*,char*) ; 
 size_t strspn (char const*,char*) ; 

__attribute__((used)) static bool marker_matches_image(const char *marker, const char *name_or_path) {
        const char *a;

        assert(marker);
        assert(name_or_path);

        a = last_path_component(marker);

        if (image_name_is_valid(name_or_path)) {
                const char *e;

                /* We shall match against an image name. In that case let's compare the last component, and optionally
                 * allow either a suffix of ".raw" or a series of "/". */

                e = startswith(a, name_or_path);
                if (!e)
                        return false;

                return
                        e[strspn(e, "/")] == 0 ||
                        streq(e, ".raw");
        } else {
                const char *b;
                size_t l;

                /* We shall match against a path. Let's ignore any prefix here though, as often there are many ways to
                 * reach the same file. However, in this mode, let's validate any file suffix. */

                l = strcspn(a, "/");
                b = last_path_component(name_or_path);

                if (strcspn(b, "/") != l)
                        return false;

                return memcmp(a, b, l) == 0;
        }
}