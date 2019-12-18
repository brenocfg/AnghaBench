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
typedef  scalar_t__ uint64_t ;
struct zip_eocd64 {scalar_t__ numentries; int /*<<< orphan*/  dir_offset; } ;
typedef  int off64_t ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  ar_stream ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ SIG_CENTRAL_DIRECTORY ; 
 int ZIP_DIR_ENTRY_FIXED_SIZE ; 
 int ar_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ar_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar_skip (int /*<<< orphan*/ *,scalar_t__) ; 
 int ar_tell (int /*<<< orphan*/ *) ; 
 scalar_t__ uint16le (int /*<<< orphan*/ *) ; 
 scalar_t__ uint32le (int /*<<< orphan*/ *) ; 

off64_t zip_find_end_of_last_directory_entry(ar_stream *stream, struct zip_eocd64 *eocd)
{
    uint8_t data[ZIP_DIR_ENTRY_FIXED_SIZE];
    uint64_t i;

    if (!ar_seek(stream, eocd->dir_offset, SEEK_SET))
        return -1;
    for (i = 0; i < eocd->numentries; i++) {
        if (ar_read(stream, data, sizeof(data)) != sizeof(data))
            return -1;
        if (uint32le(data + 0) != SIG_CENTRAL_DIRECTORY)
            return -1;
        if (!ar_skip(stream, uint16le(data + 28) + uint16le(data + 30) + uint16le(data + 32)))
            return -1;
    }

    return ar_tell(stream);
}