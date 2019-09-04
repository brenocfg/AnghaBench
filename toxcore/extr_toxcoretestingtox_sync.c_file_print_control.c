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
typedef  size_t uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  Tox ;
struct TYPE_2__ {scalar_t__ file; } ;
typedef  scalar_t__ TOX_FILE_CONTROL ;

/* Variables and functions */
 scalar_t__ TOX_FILE_CONTROL_CANCEL ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 TYPE_1__* file_recv ; 
 int /*<<< orphan*/  kill_filesender (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

void file_print_control(Tox *tox, uint32_t friend_number, uint32_t file_number, TOX_FILE_CONTROL control,
                        void *user_data)
{
    if (file_number < (1 << 15) && (control == TOX_FILE_CONTROL_CANCEL)) {
        kill_filesender(tox, file_number);
        return;
    }

    if (file_number > (1 << 15) && (control == TOX_FILE_CONTROL_CANCEL)) {
        uint8_t file_index = (file_number >> 16) - 1;
        fclose(file_recv[file_index].file);
        printf("File closed\n");
        file_recv[file_index].file = 0;
        return;
    }
}