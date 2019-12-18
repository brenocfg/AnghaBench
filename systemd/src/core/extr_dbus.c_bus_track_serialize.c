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
typedef  int /*<<< orphan*/  sd_bus_track ;
typedef  char const FILE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 int sd_bus_track_count_name (int /*<<< orphan*/ *,char const*) ; 
 char* sd_bus_track_first (int /*<<< orphan*/ *) ; 
 char* sd_bus_track_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serialize_item (char const*,char const*,char const*) ; 

void bus_track_serialize(sd_bus_track *t, FILE *f, const char *prefix) {
        const char *n;

        assert(f);
        assert(prefix);

        for (n = sd_bus_track_first(t); n; n = sd_bus_track_next(t)) {
                int c, j;

                c = sd_bus_track_count_name(t, n);
                for (j = 0; j < c; j++)
                        (void) serialize_item(f, prefix, n);
        }
}