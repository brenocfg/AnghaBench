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
typedef  scalar_t__ time_t ;
struct entry {scalar_t__ ctime; scalar_t__ hits; void* decrtime; void* counter; } ;

/* Variables and functions */
 void* COUNTER_INIT_VAL ; 
 int /*<<< orphan*/  access_entry (struct entry*) ; 
 int keyspace_size ; 
 struct entry* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int rand () ; 
 int /*<<< orphan*/  scan_entry (struct entry*) ; 
 int /*<<< orphan*/  show_entry (long,struct entry*) ; 
 scalar_t__ switch_after ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 void* to_16bit_minutes (scalar_t__) ; 

int main(void) {
    time_t start = time(NULL);
    time_t new_entry_time = start;
    time_t display_time = start;
    struct entry *entries = malloc(sizeof(*entries)*keyspace_size);
    long j;

    /* Initialize. */
    for (j = 0; j < keyspace_size; j++) {
        entries[j].counter = COUNTER_INIT_VAL;
        entries[j].decrtime = to_16bit_minutes(start);
        entries[j].hits = 0;
        entries[j].ctime = time(NULL);
    }

    while(1) {
        time_t now = time(NULL);
        long idx;

        /* Scan N random entries (simulates the eviction under maxmemory). */
        for (j = 0; j < 3; j++) {
            scan_entry(entries+(rand()%keyspace_size));
        }

        /* Access a random entry: use a power-law access pattern up to
         * 'switch_after' seconds. Then revert to flat access pattern. */
        if (now-start < switch_after) {
            /* Power law. */
            idx = 1;
            while((rand() % 21) != 0 && idx < keyspace_size) idx *= 2;
            if (idx > keyspace_size) idx = keyspace_size;
            idx = rand() % idx;
        } else {
            /* Flat. */
            idx = rand() % keyspace_size;
        }

        /* Never access entries between position 10 and 14, so that
         * we simulate what happens to new entries that are never
         * accessed VS new entries which are accessed in positions
         * 15-19.
         *
         * Also never access last 5 entry, so that we have keys which
         * are never recreated (old), and never accessed. */
        if ((idx < 10 || idx > 14) && (idx < keyspace_size-5))
            access_entry(entries+idx);

        /* Simulate the addition of new entries at positions between
         * 10 and 19, a random one every 10 seconds. */
        if (new_entry_time <= now) {
            idx = 10+(rand()%10);
            entries[idx].counter = COUNTER_INIT_VAL;
            entries[idx].decrtime = to_16bit_minutes(time(NULL));
            entries[idx].hits = 0;
            entries[idx].ctime = time(NULL);
            new_entry_time = now+10;
        }

        /* Show the first 20 entries and the last 20 entries. */
        if (display_time != now) {
            printf("=============================\n");
            printf("Current minutes time: %d\n", (int)to_16bit_minutes(now));
            printf("Access method: %s\n",
                (now-start < switch_after) ? "power-law" : "flat");

            for (j = 0; j < 20; j++)
                show_entry(j,entries+j);

            for (j = keyspace_size-20; j < keyspace_size; j++)
                show_entry(j,entries+j);
            display_time = now;
        }
    }
    return 0;
}