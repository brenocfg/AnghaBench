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
struct TYPE_3__ {char* member_0; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  const member_2; int /*<<< orphan*/  const member_1; } ;
typedef  int /*<<< orphan*/  JsonVariant ;
typedef  int /*<<< orphan*/  JsonDispatchFlags ;
typedef  TYPE_1__ JsonDispatch ;

/* Variables and functions */
#define  JSON_PERMISSIVE 134 
#define  JSON_VARIANT_ARRAY 133 
#define  JSON_VARIANT_UNSIGNED 132 
 int json_dispatch (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
#define  oci_cgroup_block_io_throttle 131 
#define  oci_cgroup_block_io_weight 130 
#define  oci_cgroup_block_io_weight_device 129 
 int /*<<< orphan*/  oci_unexpected ; 
#define  oci_unsupported 128 

__attribute__((used)) static int oci_cgroup_block_io(const char *name, JsonVariant *v, JsonDispatchFlags flags, void *userdata) {

        static const JsonDispatch table[] = {
                { "weight",                  JSON_VARIANT_UNSIGNED, oci_cgroup_block_io_weight,        0, 0               },
                { "leafWeight",              JSON_VARIANT_UNSIGNED, oci_unsupported,                   0, JSON_PERMISSIVE },
                { "weightDevice",            JSON_VARIANT_ARRAY,    oci_cgroup_block_io_weight_device, 0, 0               },
                { "throttleReadBpsDevice",   JSON_VARIANT_ARRAY,    oci_cgroup_block_io_throttle,      0, 0               },
                { "throttleWriteBpsDevice",  JSON_VARIANT_ARRAY,    oci_cgroup_block_io_throttle,      0, 0               },
                { "throttleReadIOPSDevice",  JSON_VARIANT_ARRAY,    oci_cgroup_block_io_throttle,      0, 0               },
                { "throttleWriteIOPSDevice", JSON_VARIANT_ARRAY,    oci_cgroup_block_io_throttle,      0, 0               },
                {}
        };

        return json_dispatch(v, table, oci_unexpected, flags, userdata);
}