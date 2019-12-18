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
#define  JSON_VARIANT_ARRAY 135 
#define  JSON_VARIANT_OBJECT 134 
 int json_dispatch (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
#define  oci_cgroup_block_io 133 
#define  oci_cgroup_cpu 132 
#define  oci_cgroup_devices 131 
#define  oci_cgroup_memory 130 
#define  oci_cgroup_pids 129 
 int /*<<< orphan*/  oci_unexpected ; 
#define  oci_unsupported 128 

__attribute__((used)) static int oci_resources(const char *name, JsonVariant *v, JsonDispatchFlags flags, void *userdata) {

        static const JsonDispatch table[] = {
                { "devices",        JSON_VARIANT_ARRAY,  oci_cgroup_devices,  0, 0 },
                { "memory",         JSON_VARIANT_OBJECT, oci_cgroup_memory,   0, 0 },
                { "cpu",            JSON_VARIANT_OBJECT, oci_cgroup_cpu,      0, 0 },
                { "blockIO",        JSON_VARIANT_OBJECT, oci_cgroup_block_io, 0, 0 },
                { "hugepageLimits", JSON_VARIANT_ARRAY,  oci_unsupported,     0, 0 },
                { "network",        JSON_VARIANT_OBJECT, oci_unsupported,     0, 0 },
                { "pids",           JSON_VARIANT_OBJECT, oci_cgroup_pids,     0, 0 },
                { "rdma",           JSON_VARIANT_OBJECT, oci_unsupported,     0, 0 },
                {}
        };

        return json_dispatch(v, table, oci_unexpected, flags, userdata);
}