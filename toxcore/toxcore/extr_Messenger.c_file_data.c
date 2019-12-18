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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  size_t uint32_t ;
typedef  scalar_t__ uint16_t ;
struct File_Transfers {scalar_t__ status; scalar_t__ size; scalar_t__ transferred; scalar_t__ requested; int last_packet_number; scalar_t__ slots_allocated; } ;
typedef  int int64_t ;
typedef  size_t int32_t ;
struct TYPE_7__ {TYPE_1__* friendlist; int /*<<< orphan*/  fr_c; int /*<<< orphan*/  net_crypto; } ;
struct TYPE_6__ {scalar_t__ status; int /*<<< orphan*/  friendcon_id; struct File_Transfers* file_sending; } ;
typedef  TYPE_2__ Messenger ;

/* Variables and functions */
 scalar_t__ FILESTATUS_FINISHED ; 
 scalar_t__ FILESTATUS_TRANSFERRING ; 
 scalar_t__ FRIEND_ONLINE ; 
 size_t MAX_CONCURRENT_FILE_PIPES ; 
 scalar_t__ MAX_FILE_DATA_SIZE ; 
 scalar_t__ MIN_SLOTS_FREE ; 
 scalar_t__ UINT64_MAX ; 
 scalar_t__ crypto_num_free_sendqueue_slots (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  friend_connection_crypt_connection_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ friend_not_valid (TYPE_2__ const*,size_t) ; 
 int send_file_data_packet (TYPE_2__ const*,size_t,size_t,int /*<<< orphan*/  const*,scalar_t__) ; 

int file_data(const Messenger *m, int32_t friendnumber, uint32_t filenumber, uint64_t position, const uint8_t *data,
              uint16_t length)
{
    if (friend_not_valid(m, friendnumber))
        return -1;

    if (m->friendlist[friendnumber].status != FRIEND_ONLINE)
        return -2;

    if (filenumber >= MAX_CONCURRENT_FILE_PIPES)
        return -3;

    struct File_Transfers *ft = &m->friendlist[friendnumber].file_sending[filenumber];

    if (ft->status != FILESTATUS_TRANSFERRING)
        return -4;

    if (length > MAX_FILE_DATA_SIZE)
        return -5;

    if (ft->size - ft->transferred < length) {
        return -5;
    }

    if (ft->size != UINT64_MAX && length != MAX_FILE_DATA_SIZE && (ft->transferred + length) != ft->size) {
        return -5;
    }

    if (position != ft->transferred || (ft->requested <= position && ft->size != 0)) {
        return -7;
    }

    /* Prevent file sending from filling up the entire buffer preventing messages from being sent. TODO: remove */
    if (crypto_num_free_sendqueue_slots(m->net_crypto, friend_connection_crypt_connection_id(m->fr_c,
                                        m->friendlist[friendnumber].friendcon_id)) < MIN_SLOTS_FREE)
        return -6;

    int64_t ret = send_file_data_packet(m, friendnumber, filenumber, data, length);

    if (ret != -1) {
        //TODO record packet ids to check if other received complete file.
        ft->transferred += length;

        if (ft->slots_allocated) {
            --ft->slots_allocated;
        }

        if (length != MAX_FILE_DATA_SIZE || ft->size == ft->transferred) {
            ft->status = FILESTATUS_FINISHED;
            ft->last_packet_number = ret;
        }

        return 0;
    }

    return -6;

}