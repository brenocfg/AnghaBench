#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ unit_cache_mtime; int /*<<< orphan*/  unit_path_cache; void* unit_name_map; void* unit_id_map; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 void* hashmap_free (void*) ; 
 int /*<<< orphan*/  set_free_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void manager_free_unit_name_maps(Manager *m) {
        m->unit_id_map = hashmap_free(m->unit_id_map);
        m->unit_name_map = hashmap_free(m->unit_name_map);
        m->unit_path_cache = set_free_free(m->unit_path_cache);
        m->unit_cache_mtime =  0;
}