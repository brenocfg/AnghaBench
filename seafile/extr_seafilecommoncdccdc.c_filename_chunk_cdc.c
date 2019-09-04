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
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  SeafileCrypt ;
typedef  int /*<<< orphan*/  CDCFileDescriptor ;

/* Variables and functions */
 int O_BINARY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int file_chunk_cdc (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int seaf_util_open (char const*,int) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*) ; 

int filename_chunk_cdc(const char *filename,
                       CDCFileDescriptor *file_descr,
                       SeafileCrypt *crypt,
                       gboolean write_data)
{
    int fd_src = seaf_util_open (filename, O_RDONLY | O_BINARY);
    if (fd_src < 0) {
        seaf_warning ("CDC: failed to open %s.\n", filename);
        return -1;
    }

    int ret = file_chunk_cdc (fd_src, file_descr, crypt, write_data);
    close (fd_src);
    return ret;
}