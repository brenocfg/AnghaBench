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
typedef  int pid_t ;

/* Variables and functions */
 int get_process_ppid (int,int*) ; 
 int getpid_cached () ; 

int pid_is_my_child(pid_t pid) {
        pid_t ppid;
        int r;

        if (pid <= 1)
                return false;

        r = get_process_ppid(pid, &ppid);
        if (r < 0)
                return r;

        return ppid == getpid_cached();
}