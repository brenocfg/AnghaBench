#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  Tox ;
struct TYPE_2__ {void* file; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  TOX_FILE_CONTROL_CANCEL ; 
 int /*<<< orphan*/  TOX_FILE_CONTROL_RESUME ; 
 scalar_t__ TOX_FILE_KIND_DATA ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 TYPE_1__* file_recv ; 
 void* fopen (char*,char*) ; 
 char* path ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char const*) ; 
 size_t strlen (char*) ; 
 scalar_t__ tox_file_control (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void file_request_accept(Tox *tox, uint32_t friend_number, uint32_t file_number, uint32_t type, uint64_t file_size,
                         const uint8_t *filename, size_t filename_length, void *user_data)
{
    if (type != TOX_FILE_KIND_DATA) {
        printf("Refused invalid file type.");
        tox_file_control(tox, friend_number, file_number, TOX_FILE_CONTROL_CANCEL, 0);
        return;
    }

    char fullpath[1024];
    uint32_t i;
    uint16_t rm = 0;

    for (i = 0; i < strlen((char *)filename); ++i) {
        if (filename[i] == '/')
            rm = i;
    }

    if (path[strlen(path) - 1] == '/')
        sprintf(fullpath, "%s%s", path, filename + rm + 1);
    else
        sprintf(fullpath, "%s/%s", path, filename + rm + 1);

    FILE *tempfile = fopen(fullpath, "rb");

    if (tempfile != 0) {
        fclose(tempfile);
        tox_file_control(tox, friend_number, file_number, TOX_FILE_CONTROL_CANCEL, 0);
        return;
    }

    uint8_t file_index = (file_number >> 16) - 1;
    file_recv[file_index].file = fopen(fullpath, "wb");

    if (file_recv[file_index].file == 0) {
        tox_file_control(tox, friend_number, file_number, TOX_FILE_CONTROL_CANCEL, 0);
        return;
    }

    if (tox_file_control(tox, friend_number, file_number, TOX_FILE_CONTROL_RESUME, 0)) {
        printf("Accepted file transfer. (file: %s)\n", fullpath);
    }

}