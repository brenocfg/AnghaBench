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
struct arphrd_name {int id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  assert (char const*) ; 
 struct arphrd_name* lookup_arphrd (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int arphrd_from_name(const char *name) {
        const struct arphrd_name *sc;

        assert(name);

        sc = lookup_arphrd(name, strlen(name));
        if (!sc)
                return -EINVAL;

        return sc->id;
}