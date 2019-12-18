#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  size_t int32_t ;
struct TYPE_9__ {TYPE_3__* friendlist; } ;
struct TYPE_8__ {TYPE_1__* file_receiving; TYPE_2__* file_sending; } ;
struct TYPE_7__ {scalar_t__ status; } ;
struct TYPE_6__ {scalar_t__ status; } ;
typedef  TYPE_4__ Messenger ;

/* Variables and functions */
 scalar_t__ FILESTATUS_NONE ; 
 size_t MAX_CONCURRENT_FILE_PIPES ; 

__attribute__((used)) static void break_files(const Messenger *m, int32_t friendnumber)
{
    uint32_t i;

    //TODO: Inform the client which file transfers get killed with a callback?
    for (i = 0; i < MAX_CONCURRENT_FILE_PIPES; ++i) {
        if (m->friendlist[friendnumber].file_sending[i].status != FILESTATUS_NONE)
            m->friendlist[friendnumber].file_sending[i].status = FILESTATUS_NONE;

        if (m->friendlist[friendnumber].file_receiving[i].status != FILESTATUS_NONE)
            m->friendlist[friendnumber].file_receiving[i].status = FILESTATUS_NONE;
    }
}