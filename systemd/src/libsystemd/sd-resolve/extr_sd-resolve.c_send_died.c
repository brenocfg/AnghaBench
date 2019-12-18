#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int length; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ RHeader ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 int /*<<< orphan*/  RESPONSE_DIED ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 scalar_t__ send (int,TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_died(int out_fd) {
        RHeader rh = {
                .type = RESPONSE_DIED,
                .length = sizeof(RHeader),
        };

        assert(out_fd >= 0);

        if (send(out_fd, &rh, rh.length, MSG_NOSIGNAL) < 0)
                return -errno;

        return 0;
}