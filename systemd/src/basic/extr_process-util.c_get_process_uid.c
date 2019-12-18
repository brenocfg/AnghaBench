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
typedef  int /*<<< orphan*/  uid_t ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int get_process_id (scalar_t__,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ getpid_cached () ; 
 int /*<<< orphan*/  getuid () ; 

int get_process_uid(pid_t pid, uid_t *uid) {

        if (pid == 0 || pid == getpid_cached()) {
                *uid = getuid();
                return 0;
        }

        return get_process_id(pid, "Uid:", uid);
}