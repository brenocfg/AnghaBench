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
struct TYPE_3__ {char* member_0; int /*<<< orphan*/  const member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  const member_2; int /*<<< orphan*/  const member_1; } ;
typedef  int /*<<< orphan*/  JsonVariant ;
typedef  int /*<<< orphan*/  JsonDispatchFlags ;
typedef  TYPE_1__ JsonDispatch ;

/* Variables and functions */
#define  JSON_PERMISSIVE 142 
#define  JSON_VARIANT_ARRAY 141 
#define  JSON_VARIANT_OBJECT 140 
#define  JSON_VARIANT_STRING 139 
 int json_dispatch (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
#define  oci_cgroups_path 138 
#define  oci_devices 137 
#define  oci_masked_paths 136 
#define  oci_namespaces 135 
#define  oci_readonly_paths 134 
#define  oci_resources 133 
#define  oci_rootfs_propagation 132 
#define  oci_seccomp 131 
#define  oci_sysctl 130 
#define  oci_uid_gid_mappings 129 
 int /*<<< orphan*/  oci_unexpected ; 
#define  oci_unsupported 128 

__attribute__((used)) static int oci_linux(const char *name, JsonVariant *v, JsonDispatchFlags flags, void *userdata) {

        static const JsonDispatch table[] = {
                { "namespaces",        JSON_VARIANT_ARRAY,  oci_namespaces,         0, 0               },
                { "uidMappings",       JSON_VARIANT_ARRAY,  oci_uid_gid_mappings,   0, 0               },
                { "gidMappings",       JSON_VARIANT_ARRAY,  oci_uid_gid_mappings,   0, 0               },
                { "devices",           JSON_VARIANT_ARRAY,  oci_devices,            0, 0               },
                { "cgroupsPath",       JSON_VARIANT_STRING, oci_cgroups_path,       0, 0               },
                { "resources",         JSON_VARIANT_OBJECT, oci_resources,          0, 0               },
                { "intelRdt",          JSON_VARIANT_OBJECT, oci_unsupported,        0, JSON_PERMISSIVE },
                { "sysctl",            JSON_VARIANT_OBJECT, oci_sysctl,             0, 0               },
                { "seccomp",           JSON_VARIANT_OBJECT, oci_seccomp,            0, 0               },
                { "rootfsPropagation", JSON_VARIANT_STRING, oci_rootfs_propagation, 0, 0               },
                { "maskedPaths",       JSON_VARIANT_ARRAY,  oci_masked_paths,       0, 0               },
                { "readonlyPaths",     JSON_VARIANT_ARRAY,  oci_readonly_paths,     0, 0               },
                { "mountLabel",        JSON_VARIANT_STRING, oci_unsupported,        0, JSON_PERMISSIVE },
                {}
        };

        return json_dispatch(v, table, oci_unexpected, flags, userdata);
}