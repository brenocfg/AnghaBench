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
typedef  int /*<<< orphan*/  sd_device_monitor ;
typedef  int /*<<< orphan*/  sd_device ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ sd_device_get_syspath (int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  sd_device_monitor_get_event (int /*<<< orphan*/ *) ; 
 int sd_event_exit (int /*<<< orphan*/ ,int) ; 
 int streq (char const*,char const*) ; 

__attribute__((used)) static int monitor_handler(sd_device_monitor *m, sd_device *d, void *userdata) {
        const char *s, *syspath = userdata;

        assert_se(sd_device_get_syspath(d, &s) >= 0);
        assert_se(streq(s, syspath));

        return sd_event_exit(sd_device_monitor_get_event(m), 100);
}