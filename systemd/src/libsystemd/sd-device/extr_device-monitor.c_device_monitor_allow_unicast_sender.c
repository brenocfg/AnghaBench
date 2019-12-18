#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  nl_pid; } ;
struct TYPE_12__ {TYPE_3__ nl; } ;
struct TYPE_9__ {int /*<<< orphan*/  nl_pid; } ;
struct TYPE_10__ {TYPE_1__ nl; } ;
struct TYPE_13__ {TYPE_4__ snl; TYPE_2__ snl_trusted_sender; } ;
typedef  TYPE_5__ sd_device_monitor ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  assert_return (TYPE_5__*,int /*<<< orphan*/ ) ; 

int device_monitor_allow_unicast_sender(sd_device_monitor *m, sd_device_monitor *sender) {
        assert_return(m, -EINVAL);
        assert_return(sender, -EINVAL);

        m->snl_trusted_sender.nl.nl_pid = sender->snl.nl.nl_pid;
        return 0;
}