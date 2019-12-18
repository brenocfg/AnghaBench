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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  Tox ;
struct TYPE_2__ {scalar_t__ friendnum; scalar_t__ filenumber; scalar_t__ file; } ;

/* Variables and functions */
 unsigned int NUM_FILE_SENDERS ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 TYPE_1__* file_senders ; 
 int fread (int /*<<< orphan*/ *,int,size_t,scalar_t__) ; 
 int /*<<< orphan*/  fseek (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tox_file_send_chunk (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void tox_file_chunk_request(Tox *tox, uint32_t friend_number, uint32_t file_number, uint64_t position, size_t length,
                            void *user_data)
{
    unsigned int i;

    for (i = 0; i < NUM_FILE_SENDERS; ++i) {
        /* This is slow */
        if (file_senders[i].file && file_senders[i].friendnum == friend_number && file_senders[i].filenumber == file_number) {
            if (length == 0) {
                fclose(file_senders[i].file);
                file_senders[i].file = 0;
                printf("[t] %u file transfer: %u completed\n", file_senders[i].friendnum, file_senders[i].filenumber);
                break;
            }

            fseek(file_senders[i].file, position, SEEK_SET);
            uint8_t data[length];
            int len = fread(data, 1, length, file_senders[i].file);
            tox_file_send_chunk(tox, friend_number, file_number, position, data, len, 0);
            break;
        }
    }
}