#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  attached_path; int /*<<< orphan*/  instructions; int /*<<< orphan*/  kernel_fd; } ;
typedef  TYPE_1__ BPFProgram ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  bpf_program_cgroup_detach (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BPFProgram *bpf_program_free(BPFProgram *p) {
        assert(p);

        /* Unfortunately, the kernel currently doesn't implicitly detach BPF programs from their cgroups when the last
         * fd to the BPF program is closed. This has nasty side-effects since this means that abnormally terminated
         * programs that attached one of their BPF programs to a cgroup will leave this programs pinned for good with
         * zero chance of recovery, until the cgroup is removed. This is particularly problematic if the cgroup in
         * question is the root cgroup (or any other cgroup belonging to a service that cannot be restarted during
         * operation, such as dbus), as the memory for the BPF program can only be reclaimed through a reboot. To
         * counter this, we track closely to which cgroup a program was attached to and will detach it on our own
         * whenever we close the BPF fd. */
        (void) bpf_program_cgroup_detach(p);

        safe_close(p->kernel_fd);
        free(p->instructions);
        free(p->attached_path);

        return mfree(p);
}