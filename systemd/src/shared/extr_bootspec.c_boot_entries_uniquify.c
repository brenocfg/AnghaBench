#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  show_title; scalar_t__ id; scalar_t__ machine_id; scalar_t__ version; } ;
typedef  TYPE_1__ BootEntry ;

/* Variables and functions */
 int ENOMEM ; 
 int asprintf (char**,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  boot_entry_title (TYPE_1__*) ; 
 int /*<<< orphan*/  find_nonunique (TYPE_1__*,size_t,int*) ; 
 int /*<<< orphan*/  free_and_replace (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int boot_entries_uniquify(BootEntry *entries, size_t n_entries) {
        char *s;
        size_t i;
        int r;
        bool arr[n_entries];

        assert(entries || n_entries == 0);

        /* Find _all_ non-unique titles */
        if (!find_nonunique(entries, n_entries, arr))
                return 0;

        /* Add version to non-unique titles */
        for (i = 0; i < n_entries; i++)
                if (arr[i] && entries[i].version) {
                        r = asprintf(&s, "%s (%s)", boot_entry_title(entries + i), entries[i].version);
                        if (r < 0)
                                return -ENOMEM;

                        free_and_replace(entries[i].show_title, s);
                }

        if (!find_nonunique(entries, n_entries, arr))
                return 0;

        /* Add machine-id to non-unique titles */
        for (i = 0; i < n_entries; i++)
                if (arr[i] && entries[i].machine_id) {
                        r = asprintf(&s, "%s (%s)", boot_entry_title(entries + i), entries[i].machine_id);
                        if (r < 0)
                                return -ENOMEM;

                        free_and_replace(entries[i].show_title, s);
                }

        if (!find_nonunique(entries, n_entries, arr))
                return 0;

        /* Add file name to non-unique titles */
        for (i = 0; i < n_entries; i++)
                if (arr[i]) {
                        r = asprintf(&s, "%s (%s)", boot_entry_title(entries + i), entries[i].id);
                        if (r < 0)
                                return -ENOMEM;

                        free_and_replace(entries[i].show_title, s);
                }

        return 0;
}