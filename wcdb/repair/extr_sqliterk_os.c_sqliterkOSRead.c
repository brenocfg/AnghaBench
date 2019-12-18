#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ssize_t ;
struct TYPE_3__ {scalar_t__ fd; scalar_t__ error; } ;
typedef  TYPE_1__ sqliterk_file ;
typedef  int off_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int SQLITERK_IOERR ; 
 int SQLITERK_MISUSE ; 
 int SQLITERK_OK ; 
 int SQLITERK_SHORT_READ ; 
 scalar_t__ errno ; 
 int lseek (scalar_t__,int,int /*<<< orphan*/ ) ; 
 size_t read (scalar_t__,unsigned char*,size_t) ; 

int sqliterkOSRead(sqliterk_file *file,
                   off_t offset,
                   unsigned char *data,
                   size_t *size)
{
    if (!file || file->fd < 0) {
        return SQLITERK_MISUSE;
    }
    off_t newOffset = lseek(file->fd, offset, SEEK_SET);
    if (newOffset == -1) {
        file->error = errno;
        return SQLITERK_IOERR;
    }
    size_t left = *size;
    size_t cnt = 0;
    ssize_t got = 0;
    do {
        got = read(file->fd, data, left);
        if (got < 0) {
            if (errno == EINTR) {
                got = 1;
                continue;
            }
            file->error = errno;
            return SQLITERK_IOERR;
        } else if (got > 0) {
            left -= got;
            cnt += got;
            data = data + got;
        }
    } while (got > 0 && left > 0);
    *size = cnt;
    if (left > 0) {
        return SQLITERK_SHORT_READ;
    }
    return SQLITERK_OK;
}