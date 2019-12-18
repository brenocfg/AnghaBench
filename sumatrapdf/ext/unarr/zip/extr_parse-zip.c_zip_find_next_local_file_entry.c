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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int off64_t ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  ar_stream ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ SIG_LOCAL_FILE_HEADER ; 
 int ZIP_LOCAL_ENTRY_FIXED_SIZE ; 
 scalar_t__ ar_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ar_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ uint32le (int /*<<< orphan*/ *) ; 

off64_t zip_find_next_local_file_entry(ar_stream *stream, off64_t offset)
{
    uint8_t data[512];
    int count, i;

    if (!ar_seek(stream, offset, SEEK_SET))
        return -1;
    count = (int)ar_read(stream, data, sizeof(data));

    while (count >= ZIP_LOCAL_ENTRY_FIXED_SIZE) {
        for (i = 0; i < count - 4; i++) {
            if (uint32le(data + i) == SIG_LOCAL_FILE_HEADER)
                return offset + i;
        }
        memmove(data, data + count - 4, count);
        offset += count - 4;
        count = (int)ar_read(stream, data + 4, sizeof(data) - 4) + 4;
    }

    return -1;
}