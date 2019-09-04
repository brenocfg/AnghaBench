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
struct stat {scalar_t__ st_size; } ;
struct TYPE_3__ {scalar_t__ fd; int /*<<< orphan*/  error; } ;
typedef  TYPE_1__ sqliterk_file ;

/* Variables and functions */
 int SQLITERK_IOERR ; 
 int SQLITERK_MISUSE ; 
 int SQLITERK_OK ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fstat (scalar_t__,struct stat*) ; 

int sqliterkOSFileSize(sqliterk_file *file, size_t *filesize)
{
    if (!file || file->fd < 0) {
        return SQLITERK_MISUSE;
    }
    struct stat statbuf;
    if (fstat(file->fd, &statbuf) != 0) {
        file->error = errno;
        return SQLITERK_IOERR;
    }
    *filesize = (size_t) statbuf.st_size;
    return SQLITERK_OK;
}