#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  seccomp; int /*<<< orphan*/  sysctl; int /*<<< orphan*/  network_namespace_path; int /*<<< orphan*/  n_extra_nodes; int /*<<< orphan*/  extra_nodes; int /*<<< orphan*/  supplementary_gids; int /*<<< orphan*/  properties; int /*<<< orphan*/  slice; int /*<<< orphan*/  n_oci_hooks_poststop; int /*<<< orphan*/  oci_hooks_poststop; int /*<<< orphan*/  n_oci_hooks_poststart; int /*<<< orphan*/  oci_hooks_poststart; int /*<<< orphan*/  n_oci_hooks_prestart; int /*<<< orphan*/  oci_hooks_prestart; int /*<<< orphan*/  root; int /*<<< orphan*/  bundle; int /*<<< orphan*/  n_custom_mounts; int /*<<< orphan*/  custom_mounts; int /*<<< orphan*/  expose_ports; int /*<<< orphan*/  network_zone; int /*<<< orphan*/  network_bridge; int /*<<< orphan*/  network_veth_extra; int /*<<< orphan*/  network_ipvlan; int /*<<< orphan*/  network_macvlan; int /*<<< orphan*/  network_interfaces; int /*<<< orphan*/  cpu_set; int /*<<< orphan*/  hostname; int /*<<< orphan*/  rlimit; int /*<<< orphan*/  syscall_blacklist; int /*<<< orphan*/  syscall_whitelist; int /*<<< orphan*/  working_directory; int /*<<< orphan*/  pivot_root_old; int /*<<< orphan*/  pivot_root_new; int /*<<< orphan*/  user; int /*<<< orphan*/  environment; int /*<<< orphan*/  parameters; } ;
typedef  TYPE_1__ Settings ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_set_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  custom_mount_free_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_node_array_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expose_port_free_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_oci_hooks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  rlimit_free_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_message_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seccomp_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strv_free (int /*<<< orphan*/ ) ; 

Settings* settings_free(Settings *s) {
        if (!s)
                return NULL;

        strv_free(s->parameters);
        strv_free(s->environment);
        free(s->user);
        free(s->pivot_root_new);
        free(s->pivot_root_old);
        free(s->working_directory);
        strv_free(s->syscall_whitelist);
        strv_free(s->syscall_blacklist);
        rlimit_free_all(s->rlimit);
        free(s->hostname);
        cpu_set_reset(&s->cpu_set);

        strv_free(s->network_interfaces);
        strv_free(s->network_macvlan);
        strv_free(s->network_ipvlan);
        strv_free(s->network_veth_extra);
        free(s->network_bridge);
        free(s->network_zone);
        expose_port_free_all(s->expose_ports);

        custom_mount_free_all(s->custom_mounts, s->n_custom_mounts);

        free(s->bundle);
        free(s->root);

        free_oci_hooks(s->oci_hooks_prestart, s->n_oci_hooks_prestart);
        free_oci_hooks(s->oci_hooks_poststart, s->n_oci_hooks_poststart);
        free_oci_hooks(s->oci_hooks_poststop, s->n_oci_hooks_poststop);

        free(s->slice);
        sd_bus_message_unref(s->properties);

        free(s->supplementary_gids);
        device_node_array_free(s->extra_nodes, s->n_extra_nodes);
        free(s->network_namespace_path);

        strv_free(s->sysctl);

#if HAVE_SECCOMP
        seccomp_release(s->seccomp);
#endif

        return mfree(s);
}