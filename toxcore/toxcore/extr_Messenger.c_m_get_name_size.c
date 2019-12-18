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
typedef  size_t int32_t ;
struct TYPE_6__ {TYPE_1__* friendlist; } ;
struct TYPE_5__ {int name_length; } ;
typedef  TYPE_2__ Messenger ;

/* Variables and functions */
 scalar_t__ friend_not_valid (TYPE_2__ const*,size_t) ; 

int m_get_name_size(const Messenger *m, int32_t friendnumber)
{
    if (friend_not_valid(m, friendnumber))
        return -1;

    return m->friendlist[friendnumber].name_length;
}