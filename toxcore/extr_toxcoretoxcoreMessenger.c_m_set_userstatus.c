#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_5__ {scalar_t__ userstatus; size_t numfriends; TYPE_1__* friendlist; } ;
struct TYPE_4__ {scalar_t__ userstatus_sent; } ;
typedef  TYPE_2__ Messenger ;

/* Variables and functions */
 scalar_t__ USERSTATUS_INVALID ; 

int m_set_userstatus(Messenger *m, uint8_t status)
{
    if (status >= USERSTATUS_INVALID)
        return -1;

    if (m->userstatus == status)
        return 0;

    m->userstatus = status;
    uint32_t i;

    for (i = 0; i < m->numfriends; ++i)
        m->friendlist[i].userstatus_sent = 0;

    return 0;
}