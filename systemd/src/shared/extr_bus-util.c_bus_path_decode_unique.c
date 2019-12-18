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
 int ENOMEM ; 
 int /*<<< orphan*/  assert (char**) ; 
 char* bus_label_unescape (char const*) ; 
 char* bus_label_unescape_n (char const*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char** object_path_is_valid (char const*) ; 
 char* object_path_startswith (char const*,char const*) ; 
 char* strchr (char const*,char) ; 

int bus_path_decode_unique(const char *path, const char *prefix, char **ret_sender, char **ret_external) {
        const char *p, *q;
        char *sender, *external;

        assert(object_path_is_valid(path));
        assert(object_path_is_valid(prefix));
        assert(ret_sender);
        assert(ret_external);

        p = object_path_startswith(path, prefix);
        if (!p) {
                *ret_sender = NULL;
                *ret_external = NULL;
                return 0;
        }

        q = strchr(p, '/');
        if (!q) {
                *ret_sender = NULL;
                *ret_external = NULL;
                return 0;
        }

        sender = bus_label_unescape_n(p, q - p);
        external = bus_label_unescape(q + 1);
        if (!sender || !external) {
                free(sender);
                free(external);
                return -ENOMEM;
        }

        *ret_sender = sender;
        *ret_external = external;
        return 1;
}