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
struct log {int last; int first; int stored; int /*<<< orphan*/  path; int /*<<< orphan*/  end; int /*<<< orphan*/  id; } ;
typedef  struct log gzlog ;

/* Variables and functions */
 int /*<<< orphan*/  APPEND_OP ; 
 int /*<<< orphan*/  BAIL (int) ; 
 int /*<<< orphan*/  LOGID ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int TRIGGER ; 
 int close (int) ; 
 int gzlog_compress (struct log*) ; 
 scalar_t__ log_append (struct log*,void*,size_t) ; 
 scalar_t__ log_check (struct log*) ; 
 scalar_t__ log_mark (struct log*,int /*<<< orphan*/ ) ; 
 scalar_t__ log_open (struct log*) ; 
 int /*<<< orphan*/  log_touch (struct log*) ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ write (int,void*,size_t) ; 

int gzlog_write(gzlog *logd, void *data, size_t len)
{
    int fd, ret;
    struct log *log = logd;

    /* check arguments */
    if (log == NULL || strcmp(log->id, LOGID))
        return -3;
    if (data == NULL || len <= 0)
        return 0;

    /* see if we lost the lock -- if so get it again and reload the extra
       field information (it probably changed), recover last operation if
       necessary */
    if (log_check(log) && log_open(log))
        return -1;

    /* create and write .add file */
    strcpy(log->end, ".add");
    fd = open(log->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        return -1;
    ret = (size_t)write(fd, data, len) != len;
    if (ret | close(fd))
        return -1;
    log_touch(log);

    /* mark log file with append in progress */
    if (log_mark(log, APPEND_OP))
        return -1;
    BAIL(8);

    /* append data (clears mark) */
    if (log_append(log, data, len))
        return -1;

    /* check to see if it's time to compress -- if not, then done */
    if (((log->last - log->first) >> 10) + (log->stored >> 10) < TRIGGER)
        return 0;

    /* time to compress */
    return gzlog_compress(log);
}