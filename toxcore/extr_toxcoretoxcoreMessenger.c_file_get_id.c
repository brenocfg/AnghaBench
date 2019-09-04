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
typedef  int uint32_t ;
struct File_Transfers {scalar_t__ status; int /*<<< orphan*/  id; } ;
typedef  size_t int32_t ;
struct TYPE_6__ {TYPE_1__* friendlist; } ;
struct TYPE_5__ {scalar_t__ status; struct File_Transfers* file_sending; struct File_Transfers* file_receiving; } ;
typedef  TYPE_2__ Messenger ;

/* Variables and functions */
 scalar_t__ FILESTATUS_NONE ; 
 int /*<<< orphan*/  FILE_ID_LENGTH ; 
 scalar_t__ FRIEND_ONLINE ; 
 int MAX_CONCURRENT_FILE_PIPES ; 
 scalar_t__ friend_not_valid (TYPE_2__ const*,size_t) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int file_get_id(const Messenger *m, int32_t friendnumber, uint32_t filenumber, uint8_t *file_id)
{
    if (friend_not_valid(m, friendnumber))
        return -1;

    if (m->friendlist[friendnumber].status != FRIEND_ONLINE)
        return -2;

    uint32_t temp_filenum;
    uint8_t send_receive, file_number;

    if (filenumber >= (1 << 16)) {
        send_receive = 1;
        temp_filenum = (filenumber >> 16) - 1;
    } else {
        send_receive = 0;
        temp_filenum = filenumber;
    }

    if (temp_filenum >= MAX_CONCURRENT_FILE_PIPES)
        return -2;

    file_number = temp_filenum;

    struct File_Transfers *ft;

    if (send_receive) {
        ft = &m->friendlist[friendnumber].file_receiving[file_number];
    } else {
        ft = &m->friendlist[friendnumber].file_sending[file_number];
    }

    if (ft->status == FILESTATUS_NONE)
        return -2;

    memcpy(file_id, ft->id, FILE_ID_LENGTH);
    return 0;
}