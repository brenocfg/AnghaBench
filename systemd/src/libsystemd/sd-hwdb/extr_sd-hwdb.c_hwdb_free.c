#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  st_size; } ;
struct TYPE_9__ {int /*<<< orphan*/  properties; int /*<<< orphan*/  f; TYPE_1__ st; scalar_t__ map; } ;
typedef  TYPE_2__ sd_hwdb ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 TYPE_2__* mfree (TYPE_2__*) ; 
 int /*<<< orphan*/  munmap (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ordered_hashmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_fclose (int /*<<< orphan*/ ) ; 

__attribute__((used)) static sd_hwdb *hwdb_free(sd_hwdb *hwdb) {
        assert(hwdb);

        if (hwdb->map)
                munmap((void *)hwdb->map, hwdb->st.st_size);
        safe_fclose(hwdb->f);
        ordered_hashmap_free(hwdb->properties);
        return mfree(hwdb);
}