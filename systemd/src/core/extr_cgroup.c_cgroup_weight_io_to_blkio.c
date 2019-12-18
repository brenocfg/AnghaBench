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
typedef  int uint64_t ;

/* Variables and functions */
 int CGROUP_BLKIO_WEIGHT_DEFAULT ; 
 int /*<<< orphan*/  CGROUP_BLKIO_WEIGHT_MAX ; 
 int /*<<< orphan*/  CGROUP_BLKIO_WEIGHT_MIN ; 
 int CGROUP_WEIGHT_DEFAULT ; 
 int CLAMP (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t cgroup_weight_io_to_blkio(uint64_t io_weight) {
        return CLAMP(io_weight * CGROUP_BLKIO_WEIGHT_DEFAULT / CGROUP_WEIGHT_DEFAULT,
                     CGROUP_BLKIO_WEIGHT_MIN, CGROUP_BLKIO_WEIGHT_MAX);
}