#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_13__ {scalar_t__ memory_high; scalar_t__ memory_max; scalar_t__ memory_swap_max; } ;
typedef  TYPE_1__ Unit ;
typedef  int /*<<< orphan*/  CGroupMask ;
typedef  TYPE_1__ CGroupContext ;

/* Variables and functions */
 scalar_t__ CGROUP_LIMIT_MAX ; 
 int /*<<< orphan*/  CGROUP_MASK_MEMORY ; 
 int EINVAL ; 
 int ENODATA ; 
 int /*<<< orphan*/  FLAGS_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PAGE_ALIGN_DOWN (scalar_t__) ; 
 int /*<<< orphan*/  SPECIAL_ROOT_SLICE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int cg_all_unified () ; 
 int log_debug_errno (int,char*) ; 
 int log_unit_debug_errno (TYPE_1__*,int,char*,char const*) ; 
 scalar_t__ streq (char const*,char*) ; 
 scalar_t__ unit_get_ancestor_memory_low (TYPE_1__*) ; 
 scalar_t__ unit_get_ancestor_memory_min (TYPE_1__*) ; 
 TYPE_1__* unit_get_cgroup_context (TYPE_1__*) ; 
 int unit_get_kernel_memory_limit (TYPE_1__*,char const*,scalar_t__*) ; 
 int /*<<< orphan*/  unit_get_target_mask (TYPE_1__*) ; 
 scalar_t__ unit_has_name (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unit_compare_memory_limit(Unit *u, const char *property_name, uint64_t *ret_unit_value, uint64_t *ret_kernel_value) {
        CGroupContext *c;
        CGroupMask m;
        const char *file;
        uint64_t unit_value;
        int r;

        /* Compare kernel memcg configuration against our internal systemd state. Unsupported (and will
         * return -ENODATA) on cgroup v1.
         *
         * Returns:
         *
         * <0: On error.
         *  0: If the kernel memory setting doesn't match our configuration.
         * >0: If the kernel memory setting matches our configuration.
         *
         * The following values are only guaranteed to be populated on return >=0:
         *
         * - ret_unit_value will contain our internal expected value for the unit, page-aligned.
         * - ret_kernel_value will contain the actual value presented by the kernel. */

        assert(u);

        r = cg_all_unified();
        if (r < 0)
                return log_debug_errno(r, "Failed to determine cgroup hierarchy version: %m");

        /* Unsupported on v1.
         *
         * We don't return ENOENT, since that could actually mask a genuine problem where somebody else has
         * silently masked the controller. */
        if (r == 0)
                return -ENODATA;

        /* The root slice doesn't have any controller files, so we can't compare anything. */
        if (unit_has_name(u, SPECIAL_ROOT_SLICE))
                return -ENODATA;

        /* It's possible to have MemoryFoo set without systemd wanting to have the memory controller enabled,
         * for example, in the case of DisableControllers= or cgroup_disable on the kernel command line. To
         * avoid specious errors in these scenarios, check that we even expect the memory controller to be
         * enabled at all. */
        m = unit_get_target_mask(u);
        if (!FLAGS_SET(m, CGROUP_MASK_MEMORY))
                return -ENODATA;

        c = unit_get_cgroup_context(u);
        assert(c);

        if (streq(property_name, "MemoryLow")) {
                unit_value = unit_get_ancestor_memory_low(u);
                file = "memory.low";
        } else if (streq(property_name, "MemoryMin")) {
                unit_value = unit_get_ancestor_memory_min(u);
                file = "memory.min";
        } else if (streq(property_name, "MemoryHigh")) {
                unit_value = c->memory_high;
                file = "memory.high";
        } else if (streq(property_name, "MemoryMax")) {
                unit_value = c->memory_max;
                file = "memory.max";
        } else if (streq(property_name, "MemorySwapMax")) {
                unit_value = c->memory_swap_max;
                file = "memory.swap.max";
        } else
                return -EINVAL;

        r = unit_get_kernel_memory_limit(u, file, ret_kernel_value);
        if (r < 0)
                return log_unit_debug_errno(u, r, "Failed to parse %s: %m", file);

        /* It's intended (soon) in a future kernel to not expose cgroup memory limits rounded to page
         * boundaries, but instead separate the user-exposed limit, which is whatever userspace told us, from
         * our internal page-counting. To support those future kernels, just check the value itself first
         * without any page-alignment. */
        if (*ret_kernel_value == unit_value) {
                *ret_unit_value = unit_value;
                return 1;
        }

        /* The current kernel behaviour, by comparison, is that even if you write a particular number of
         * bytes into a cgroup memory file, it always returns that number page-aligned down (since the kernel
         * internally stores cgroup limits in pages). As such, so long as it aligns properly, everything is
         * cricket. */
        if (unit_value != CGROUP_LIMIT_MAX)
                unit_value = PAGE_ALIGN_DOWN(unit_value);

        *ret_unit_value = unit_value;

        return *ret_kernel_value == *ret_unit_value;
}