#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uintmax_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  properties; } ;
typedef  TYPE_1__ Settings ;
typedef  int /*<<< orphan*/  JsonVariant ;
typedef  int /*<<< orphan*/  JsonDispatchFlags ;

/* Variables and functions */
 scalar_t__ CGROUP_BLKIO_WEIGHT_MAX ; 
 scalar_t__ CGROUP_BLKIO_WEIGHT_MIN ; 
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int bus_log_create_error (int) ; 
 int json_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ json_variant_unsigned (int /*<<< orphan*/ *) ; 
 int sd_bus_message_append (int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int settings_allocate_properties (TYPE_1__*) ; 

__attribute__((used)) static int oci_cgroup_block_io_weight(const char *name, JsonVariant *v, JsonDispatchFlags flags, void *userdata) {
        Settings *s = userdata;
        uintmax_t k;
        int r;

        assert(s);

        k = json_variant_unsigned(v);
        if (k < CGROUP_BLKIO_WEIGHT_MIN || k > CGROUP_BLKIO_WEIGHT_MAX)
                return json_log(v, flags, SYNTHETIC_ERRNO(ERANGE),
                                "Block I/O weight out of range.");

        r = settings_allocate_properties(s);
        if (r < 0)
                return r;

        r = sd_bus_message_append(s->properties, "(sv)", "BlockIOWeight", "t", (uint64_t) k);
        if (r < 0)
                return bus_log_create_error(r);

        return 0;
}