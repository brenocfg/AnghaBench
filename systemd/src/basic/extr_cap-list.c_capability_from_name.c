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
struct capability_name {int id; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t ELEMENTSOF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  capability_names ; 
 struct capability_name* lookup_capability (char const*,int /*<<< orphan*/ ) ; 
 int safe_atoi (char const*,int*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int capability_from_name(const char *name) {
        const struct capability_name *sc;
        int r, i;

        assert(name);

        /* Try to parse numeric capability */
        r = safe_atoi(name, &i);
        if (r >= 0) {
                if (i >= 0 && (size_t) i < ELEMENTSOF(capability_names))
                        return i;
                else
                        return -EINVAL;
        }

        /* Try to parse string capability */
        sc = lookup_capability(name, strlen(name));
        if (!sc)
                return -EINVAL;

        return sc->id;
}