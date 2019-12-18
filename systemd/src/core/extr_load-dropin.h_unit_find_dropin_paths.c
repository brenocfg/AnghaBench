#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  names; TYPE_2__* manager; } ;
typedef  TYPE_3__ Unit ;
struct TYPE_6__ {int /*<<< orphan*/  search_path; } ;
struct TYPE_7__ {int /*<<< orphan*/  unit_path_cache; TYPE_1__ lookup_paths; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int unit_file_find_dropin_paths (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char***) ; 

__attribute__((used)) static inline int unit_find_dropin_paths(Unit *u, char ***paths) {
        assert(u);

        return unit_file_find_dropin_paths(NULL,
                                           u->manager->lookup_paths.search_path,
                                           u->manager->unit_path_cache,
                                           ".d", ".conf",
                                           u->names,
                                           paths);
}