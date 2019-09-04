#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t int32_t ;
struct TYPE_6__ {TYPE_1__* friendlist; } ;
struct TYPE_5__ {int /*<<< orphan*/  status; } ;
typedef  TYPE_2__ Messenger ;

/* Variables and functions */
 int /*<<< orphan*/  check_friend_connectionstatus (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 

void set_friend_status(Messenger *m, int32_t friendnumber, uint8_t status)
{
    check_friend_connectionstatus(m, friendnumber, status);
    m->friendlist[friendnumber].status = status;
}