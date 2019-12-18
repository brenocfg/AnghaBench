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
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert_cc (int) ; 
 int get_process_id (scalar_t__,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getgid () ; 
 scalar_t__ getpid_cached () ; 

int get_process_gid(pid_t pid, gid_t *gid) {

        if (pid == 0 || pid == getpid_cached()) {
                *gid = getgid();
                return 0;
        }

        assert_cc(sizeof(uid_t) == sizeof(gid_t));
        return get_process_id(pid, "Gid:", gid);
}