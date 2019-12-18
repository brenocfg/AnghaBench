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
struct socket_info {int /*<<< orphan*/  type; int /*<<< orphan*/  path; scalar_t__ machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct socket_info const*) ; 
 int strcasecmp (scalar_t__,scalar_t__) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int socket_info_compare(const struct socket_info *a, const struct socket_info *b) {
        int r;

        assert(a);
        assert(b);

        if (!a->machine && b->machine)
                return -1;
        if (a->machine && !b->machine)
                return 1;
        if (a->machine && b->machine) {
                r = strcasecmp(a->machine, b->machine);
                if (r != 0)
                        return r;
        }

        r = strcmp(a->path, b->path);
        if (r == 0)
                r = strcmp(a->type, b->type);

        return r;
}