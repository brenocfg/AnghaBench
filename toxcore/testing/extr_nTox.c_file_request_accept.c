#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  char uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  Tox ;

/* Variables and functions */
 int /*<<< orphan*/  TOX_FILE_CONTROL_CANCEL ; 
 int /*<<< orphan*/  TOX_FILE_CONTROL_RESUME ; 
 scalar_t__ TOX_FILE_KIND_DATA ; 
 int /*<<< orphan*/  new_lines (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__,scalar_t__,...) ; 
 scalar_t__ tox_file_control (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void file_request_accept(Tox *tox, uint32_t friend_number, uint32_t file_number, uint32_t type, uint64_t file_size,
                         const uint8_t *filename, size_t filename_length, void *user_data)
{
    if (type != TOX_FILE_KIND_DATA) {
        new_lines("Refused invalid file type.");
        tox_file_control(tox, friend_number, file_number, TOX_FILE_CONTROL_CANCEL, 0);
        return;
    }

    char msg[512];
    sprintf(msg, "[t] %u is sending us: %s of size %llu", friend_number, filename, (long long unsigned int)file_size);
    new_lines(msg);

    if (tox_file_control(tox, friend_number, file_number, TOX_FILE_CONTROL_RESUME, 0)) {
        sprintf(msg, "Accepted file transfer. (saving file as: %u.%u.bin)", friend_number, file_number);
        new_lines(msg);
    } else
        new_lines("Could not accept file transfer.");
}