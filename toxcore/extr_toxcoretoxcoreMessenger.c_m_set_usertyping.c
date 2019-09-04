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
typedef  int uint8_t ;
typedef  size_t int32_t ;
struct TYPE_6__ {TYPE_1__* friendlist; } ;
struct TYPE_5__ {int user_istyping; scalar_t__ user_istyping_sent; } ;
typedef  TYPE_2__ Messenger ;

/* Variables and functions */
 scalar_t__ friend_not_valid (TYPE_2__*,size_t) ; 

int m_set_usertyping(Messenger *m, int32_t friendnumber, uint8_t is_typing)

{
    if (is_typing != 0 && is_typing != 1)
        return -1;

    if (friend_not_valid(m, friendnumber))
        return -1;

    if (m->friendlist[friendnumber].user_istyping == is_typing)
        return 0;

    m->friendlist[friendnumber].user_istyping = is_typing;
    m->friendlist[friendnumber].user_istyping_sent = 0;

    return 0;
}