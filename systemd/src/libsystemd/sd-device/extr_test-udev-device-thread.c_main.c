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
struct udev_device {int dummy; } ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct udev_device**) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread ; 
 int udev_device_get_properties_list_entry (struct udev_device*) ; 
 struct udev_device* udev_device_new_from_syspath (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ unsetenv (char*) ; 

int main(int argc, char *argv[]) {
        struct udev_device *loopback;
        pthread_t t;

        assert_se(unsetenv("SYSTEMD_MEMPOOL") == 0);

        assert_se(loopback = udev_device_new_from_syspath(NULL, "/sys/class/net/lo"));

        assert_se(udev_device_get_properties_list_entry(loopback));

        assert_se(pthread_create(&t, NULL, thread, &loopback) == 0);
        assert_se(pthread_join(t, NULL) == 0);

        assert_se(!loopback);

        return 0;
}