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

/* Variables and functions */
 int /*<<< orphan*/  SIGINT ; 
 char* arg_kill_who ; 
 int /*<<< orphan*/  arg_signal ; 
 int kill_machine (int,char**,void*) ; 

__attribute__((used)) static int reboot_machine(int argc, char *argv[], void *userdata) {
        arg_kill_who = "leader";
        arg_signal = SIGINT; /* sysvinit + systemd */

        return kill_machine(argc, argv, userdata);
}