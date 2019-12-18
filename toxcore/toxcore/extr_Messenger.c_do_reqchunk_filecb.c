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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint16_t ;
struct File_Transfers {scalar_t__ status; scalar_t__ transferred; unsigned int slots_allocated; scalar_t__ paused; scalar_t__ size; scalar_t__ requested; int /*<<< orphan*/  last_packet_number; } ;
typedef  size_t int32_t ;
struct TYPE_9__ {int /*<<< orphan*/  file_reqchunk_userdata; int /*<<< orphan*/  (* file_reqchunk ) (TYPE_2__*,size_t,unsigned int,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ;TYPE_1__* friendlist; int /*<<< orphan*/  fr_c; int /*<<< orphan*/  net_crypto; } ;
struct TYPE_8__ {unsigned int num_sending_files; int /*<<< orphan*/  friendcon_id; struct File_Transfers* file_sending; } ;
typedef  TYPE_2__ Messenger ;

/* Variables and functions */
 scalar_t__ FILESTATUS_FINISHED ; 
 scalar_t__ FILESTATUS_NONE ; 
 scalar_t__ FILESTATUS_TRANSFERRING ; 
 scalar_t__ FILE_PAUSE_NOT ; 
 unsigned int MAX_CONCURRENT_FILE_PIPES ; 
 scalar_t__ MAX_FILE_DATA_SIZE ; 
 int MIN_SLOTS_FREE ; 
 int crypto_num_free_sendqueue_slots (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_data (TYPE_2__*,size_t,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  friend_connection_crypt_connection_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ friend_received_packet (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ max_speed_reached (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,size_t,unsigned int,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,size_t,unsigned int,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_reqchunk_filecb(Messenger *m, int32_t friendnumber)
{
    if (!m->friendlist[friendnumber].num_sending_files)
        return;

    int free_slots = crypto_num_free_sendqueue_slots(m->net_crypto, friend_connection_crypt_connection_id(m->fr_c,
                     m->friendlist[friendnumber].friendcon_id));

    if (free_slots < MIN_SLOTS_FREE) {
        free_slots = 0;
    } else {
        free_slots -= MIN_SLOTS_FREE;
    }

    unsigned int i, num = m->friendlist[friendnumber].num_sending_files;

    for (i = 0; i < MAX_CONCURRENT_FILE_PIPES; ++i) {
        struct File_Transfers *ft = &m->friendlist[friendnumber].file_sending[i];

        if (ft->status != FILESTATUS_NONE) {
            --num;

            if (ft->status == FILESTATUS_FINISHED) {
                /* Check if file was entirely sent. */
                if (friend_received_packet(m, friendnumber, ft->last_packet_number) == 0) {
                    if (m->file_reqchunk)
                        (*m->file_reqchunk)(m, friendnumber, i, ft->transferred, 0, m->file_reqchunk_userdata);

                    ft->status = FILESTATUS_NONE;
                    --m->friendlist[friendnumber].num_sending_files;
                }
            }

            /* TODO: if file is too slow, switch to the next. */
            if (ft->slots_allocated > (unsigned int)free_slots) {
                free_slots = 0;
            } else {
                free_slots -= ft->slots_allocated;
            }
        }

        while (ft->status == FILESTATUS_TRANSFERRING && (ft->paused == FILE_PAUSE_NOT)) {
            if (max_speed_reached(m->net_crypto, friend_connection_crypt_connection_id(m->fr_c,
                                  m->friendlist[friendnumber].friendcon_id))) {
                free_slots = 0;
            }

            if (free_slots == 0)
                break;

            uint16_t length = MAX_FILE_DATA_SIZE;

            if (ft->size == 0) {
                /* Send 0 data to friend if file is 0 length. */
                file_data(m, friendnumber, i, 0, 0, 0);
                break;
            }

            if (ft->size == ft->requested) {
                break;
            }

            if (ft->size - ft->requested < length) {
                length = ft->size - ft->requested;
            }

            ++ft->slots_allocated;

            uint64_t position = ft->requested;
            ft->requested += length;

            if (m->file_reqchunk)
                (*m->file_reqchunk)(m, friendnumber, i, position, length, m->file_reqchunk_userdata);

            --free_slots;

        }

        if (num == 0)
            break;
    }
}