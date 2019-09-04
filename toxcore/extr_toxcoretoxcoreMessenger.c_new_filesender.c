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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct File_Transfers {scalar_t__ status; int /*<<< orphan*/  id; int /*<<< orphan*/  paused; scalar_t__ slots_allocated; scalar_t__ requested; scalar_t__ transferred; int /*<<< orphan*/  size; } ;
typedef  size_t int32_t ;
struct TYPE_7__ {TYPE_1__* friendlist; } ;
struct TYPE_6__ {int /*<<< orphan*/  num_sending_files; struct File_Transfers* file_sending; } ;
typedef  TYPE_2__ Messenger ;

/* Variables and functions */
 scalar_t__ FILESTATUS_NONE ; 
 scalar_t__ FILESTATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  FILE_ID_LENGTH ; 
 int /*<<< orphan*/  FILE_PAUSE_NOT ; 
 size_t MAX_CONCURRENT_FILE_PIPES ; 
 int /*<<< orphan*/  MAX_FILENAME_LENGTH ; 
 scalar_t__ file_sendrequest (TYPE_2__ const*,size_t,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ friend_not_valid (TYPE_2__ const*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

long int new_filesender(const Messenger *m, int32_t friendnumber, uint32_t file_type, uint64_t filesize,
                        const uint8_t *file_id, const uint8_t *filename, uint16_t filename_length)
{
    if (friend_not_valid(m, friendnumber))
        return -1;

    if (filename_length > MAX_FILENAME_LENGTH)
        return -2;

    uint32_t i;

    for (i = 0; i < MAX_CONCURRENT_FILE_PIPES; ++i) {
        if (m->friendlist[friendnumber].file_sending[i].status == FILESTATUS_NONE)
            break;
    }

    if (i == MAX_CONCURRENT_FILE_PIPES)
        return -3;

    if (file_sendrequest(m, friendnumber, i, file_type, filesize, file_id, filename, filename_length) == 0)
        return -4;

    struct File_Transfers *ft = &m->friendlist[friendnumber].file_sending[i];
    ft->status = FILESTATUS_NOT_ACCEPTED;
    ft->size = filesize;
    ft->transferred = 0;
    ft->requested = 0;
    ft->slots_allocated = 0;
    ft->paused = FILE_PAUSE_NOT;
    memcpy(ft->id, file_id, FILE_ID_LENGTH);

    ++m->friendlist[friendnumber].num_sending_files;

    return i;
}