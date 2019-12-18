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
struct cpu_data {int /*<<< orphan*/  cpu_set; } ;
typedef  int /*<<< orphan*/  JsonVariant ;
typedef  int /*<<< orphan*/  JsonDispatchFlags ;
typedef  int /*<<< orphan*/  CPUSet ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct cpu_data*) ; 
 int /*<<< orphan*/  assert_se (char const*) ; 
 int /*<<< orphan*/  cpu_set_reset (int /*<<< orphan*/ *) ; 
 int json_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,char const*) ; 
 char* json_variant_string (int /*<<< orphan*/ *) ; 
 int parse_cpu_set (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int oci_cgroup_cpu_cpus(const char *name, JsonVariant *v, JsonDispatchFlags flags, void *userdata) {
        struct cpu_data *data = userdata;
        CPUSet set;
        const char *n;
        int r;

        assert(data);

        assert_se(n = json_variant_string(v));

        r = parse_cpu_set(n, &set);
        if (r < 0)
                return json_log(v, flags, r, "Failed to parse CPU set specification: %s", n);

        cpu_set_reset(&data->cpu_set);
        data->cpu_set = set;

        return 0;
}