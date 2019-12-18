#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  line; int /*<<< orphan*/  filename; } ;
struct TYPE_4__ {scalar_t__ family; scalar_t__ lladdr_size; TYPE_2__* section; } ;
typedef  TYPE_1__ Neighbor ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 int EINVAL ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int) ; 
 int log_warning_errno (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ section_is_invalid (TYPE_2__*) ; 

int neighbor_section_verify(Neighbor *neighbor) {
        if (section_is_invalid(neighbor->section))
                return -EINVAL;

        if (neighbor->family == AF_UNSPEC)
                return log_warning_errno(SYNTHETIC_ERRNO(EINVAL),
                                         "%s: Neighbor section without Address= configured. "
                                         "Ignoring [Neighbor] section from line %u.",
                                         neighbor->section->filename, neighbor->section->line);

        if (neighbor->lladdr_size == 0)
                return log_warning_errno(SYNTHETIC_ERRNO(EINVAL),
                                         "%s: Neighbor section without LinkLayerAddress= configured. "
                                         "Ignoring [Neighbor] section from line %u.",
                                         neighbor->section->filename, neighbor->section->line);

        return 0;
}