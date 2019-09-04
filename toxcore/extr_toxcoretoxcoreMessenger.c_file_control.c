#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct File_Transfers {scalar_t__ status; int paused; } ;
typedef  size_t int32_t ;
struct TYPE_7__ {TYPE_1__* friendlist; } ;
struct TYPE_6__ {scalar_t__ status; int /*<<< orphan*/  num_sending_files; struct File_Transfers* file_sending; struct File_Transfers* file_receiving; } ;
typedef  TYPE_2__ Messenger ;

/* Variables and functions */
 unsigned int FILECONTROL_ACCEPT ; 
 unsigned int FILECONTROL_KILL ; 
 unsigned int FILECONTROL_PAUSE ; 
 scalar_t__ FILESTATUS_NONE ; 
 scalar_t__ FILESTATUS_NOT_ACCEPTED ; 
 scalar_t__ FILESTATUS_TRANSFERRING ; 
 int FILE_PAUSE_OTHER ; 
 int FILE_PAUSE_US ; 
 scalar_t__ FRIEND_ONLINE ; 
 int MAX_CONCURRENT_FILE_PIPES ; 
 scalar_t__ friend_not_valid (TYPE_2__ const*,size_t) ; 
 scalar_t__ send_file_control_packet (TYPE_2__ const*,size_t,int,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int file_control(const Messenger *m, int32_t friendnumber, uint32_t filenumber, unsigned int control)
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
        return -3;

    file_number = temp_filenum;

    struct File_Transfers *ft;

    if (send_receive) {
        ft = &m->friendlist[friendnumber].file_receiving[file_number];
    } else {
        ft = &m->friendlist[friendnumber].file_sending[file_number];
    }

    if (ft->status == FILESTATUS_NONE)
        return -3;

    if (control > FILECONTROL_KILL)
        return -4;

    if (control == FILECONTROL_PAUSE && ((ft->paused & FILE_PAUSE_US) || ft->status != FILESTATUS_TRANSFERRING))
        return -5;

    if (control == FILECONTROL_ACCEPT) {
        if (ft->status == FILESTATUS_TRANSFERRING) {
            if (!(ft->paused & FILE_PAUSE_US)) {
                if (ft->paused & FILE_PAUSE_OTHER) {
                    return -6;
                } else {
                    return -7;
                }
            }
        } else {
            if (ft->status != FILESTATUS_NOT_ACCEPTED)
                return -7;

            if (!send_receive)
                return -6;
        }
    }

    if (send_file_control_packet(m, friendnumber, send_receive, file_number, control, 0, 0)) {
        if (control == FILECONTROL_KILL) {
            ft->status = FILESTATUS_NONE;

            if (send_receive == 0) {
                --m->friendlist[friendnumber].num_sending_files;
            }
        } else if (control == FILECONTROL_PAUSE) {
            ft->paused |= FILE_PAUSE_US;
        } else if (control == FILECONTROL_ACCEPT) {
            ft->status = FILESTATUS_TRANSFERRING;

            if (ft->paused & FILE_PAUSE_US) {
                ft->paused ^=  FILE_PAUSE_US;
            }
        }
    } else {
        return -8;
    }

    return 0;
}