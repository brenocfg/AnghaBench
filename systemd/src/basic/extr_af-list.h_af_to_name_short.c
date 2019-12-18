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
 int AF_UNSPEC ; 
 char* af_to_name (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  startswith (char const*,char*) ; 

__attribute__((used)) static inline const char* af_to_name_short(int id) {
        const char *f;

        if (id == AF_UNSPEC)
                return "*";

        f = af_to_name(id);
        if (!f)
                return "unknown";

        assert(startswith(f, "AF_"));
        return f + 3;
}