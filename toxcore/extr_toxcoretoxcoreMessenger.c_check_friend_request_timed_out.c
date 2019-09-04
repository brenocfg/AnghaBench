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
typedef  scalar_t__ uint64_t ;
typedef  size_t uint32_t ;
struct TYPE_6__ {scalar_t__ friendrequest_lastsent; int friendrequest_timeout; } ;
struct TYPE_5__ {TYPE_2__* friendlist; } ;
typedef  TYPE_1__ Messenger ;
typedef  TYPE_2__ Friend ;

/* Variables and functions */
 int /*<<< orphan*/  FRIEND_ADDED ; 
 int /*<<< orphan*/  set_friend_status (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_friend_request_timed_out(Messenger *m, uint32_t i, uint64_t t)
{
    Friend *f = &m->friendlist[i];

    if (f->friendrequest_lastsent + f->friendrequest_timeout < t) {
        set_friend_status(m, i, FRIEND_ADDED);
        /* Double the default timeout every time if friendrequest is assumed
         * to have been sent unsuccessfully.
         */
        f->friendrequest_timeout *= 2;
    }
}