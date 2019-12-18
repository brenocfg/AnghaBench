#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct File_Transfers {scalar_t__ status; int paused; scalar_t__ size; scalar_t__ requested; scalar_t__ transferred; } ;
typedef  int /*<<< orphan*/  position ;
typedef  size_t int32_t ;
struct TYPE_9__ {TYPE_1__* friendlist; int /*<<< orphan*/  file_filecontrol_userdata; int /*<<< orphan*/  (* file_filecontrol ) (TYPE_2__*,size_t,int,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  num_sending_files; struct File_Transfers* file_sending; struct File_Transfers* file_receiving; } ;
typedef  TYPE_2__ Messenger ;

/* Variables and functions */
 int FILECONTROL_ACCEPT ; 
 int FILECONTROL_KILL ; 
 int FILECONTROL_PAUSE ; 
 int FILECONTROL_SEEK ; 
 scalar_t__ FILESTATUS_NONE ; 
 scalar_t__ FILESTATUS_NOT_ACCEPTED ; 
 scalar_t__ FILESTATUS_TRANSFERRING ; 
 int FILE_PAUSE_OTHER ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int*,int) ; 
 int /*<<< orphan*/  net_to_host (int*,int) ; 
 int /*<<< orphan*/  send_file_control_packet (TYPE_2__*,size_t,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,size_t,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,size_t,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,size_t,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_filecontrol(Messenger *m, int32_t friendnumber, uint8_t receive_send, uint8_t filenumber,
                              uint8_t control_type, uint8_t *data, uint16_t length)
{
    if (receive_send > 1)
        return -1;

    if (control_type > FILECONTROL_SEEK)
        return -1;

    uint32_t real_filenumber = filenumber;
    struct File_Transfers *ft;

    if (receive_send == 0) {
        real_filenumber += 1;
        real_filenumber <<= 16;
        ft = &m->friendlist[friendnumber].file_receiving[filenumber];
    } else {
        ft = &m->friendlist[friendnumber].file_sending[filenumber];
    }

    if (ft->status == FILESTATUS_NONE) {
        /* File transfer doesn't exist, tell the other to kill it. */
        send_file_control_packet(m, friendnumber, !receive_send, filenumber, FILECONTROL_KILL, 0, 0);
        return -1;
    }

    if (control_type == FILECONTROL_ACCEPT) {
        if (receive_send && ft->status == FILESTATUS_NOT_ACCEPTED) {
            ft->status = FILESTATUS_TRANSFERRING;
        } else {
            if (ft->paused & FILE_PAUSE_OTHER) {
                ft->paused ^= FILE_PAUSE_OTHER;
            } else {
                return -1;
            }
        }

        if (m->file_filecontrol)
            (*m->file_filecontrol)(m, friendnumber, real_filenumber, control_type, m->file_filecontrol_userdata);
    } else if (control_type == FILECONTROL_PAUSE) {
        if ((ft->paused & FILE_PAUSE_OTHER) || ft->status != FILESTATUS_TRANSFERRING) {
            return -1;
        }

        ft->paused |= FILE_PAUSE_OTHER;

        if (m->file_filecontrol)
            (*m->file_filecontrol)(m, friendnumber, real_filenumber, control_type, m->file_filecontrol_userdata);
    } else if (control_type == FILECONTROL_KILL) {

        if (m->file_filecontrol)
            (*m->file_filecontrol)(m, friendnumber, real_filenumber, control_type, m->file_filecontrol_userdata);

        ft->status = FILESTATUS_NONE;

        if (receive_send) {
            --m->friendlist[friendnumber].num_sending_files;
        }

    } else if (control_type == FILECONTROL_SEEK) {
        uint64_t position;

        if (length != sizeof(position)) {
            return -1;
        }

        /* seek can only be sent by the receiver to seek before resuming broken transfers. */
        if (ft->status != FILESTATUS_NOT_ACCEPTED || !receive_send) {
            return -1;
        }

        memcpy(&position, data, sizeof(position));
        net_to_host((uint8_t *) &position, sizeof(position));

        if (position >= ft->size) {
            return -1;
        }

        ft->transferred = ft->requested = position;
    } else {
        return -1;
    }

    return 0;
}