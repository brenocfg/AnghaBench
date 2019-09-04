#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  size_t int32_t ;
struct TYPE_10__ {TYPE_3__* friendlist; } ;
struct TYPE_9__ {TYPE_2__* file_receiving; TYPE_1__* file_sending; } ;
struct TYPE_8__ {scalar_t__ status; scalar_t__ transferred; scalar_t__ size; } ;
struct TYPE_7__ {scalar_t__ status; scalar_t__ transferred; scalar_t__ size; } ;
typedef  TYPE_4__ Messenger ;

/* Variables and functions */
 scalar_t__ FILESTATUS_NONE ; 
 scalar_t__ friend_not_valid (TYPE_4__ const*,size_t) ; 

uint64_t file_dataremaining(const Messenger *m, int32_t friendnumber, uint8_t filenumber, uint8_t send_receive)
{
    if (friend_not_valid(m, friendnumber))
        return 0;

    if (send_receive == 0) {
        if (m->friendlist[friendnumber].file_sending[filenumber].status == FILESTATUS_NONE)
            return 0;

        return m->friendlist[friendnumber].file_sending[filenumber].size -
               m->friendlist[friendnumber].file_sending[filenumber].transferred;
    } else {
        if (m->friendlist[friendnumber].file_receiving[filenumber].status == FILESTATUS_NONE)
            return 0;

        return m->friendlist[friendnumber].file_receiving[filenumber].size -
               m->friendlist[friendnumber].file_receiving[filenumber].transferred;
    }
}