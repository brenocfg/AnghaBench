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
struct stat {int st_ctime; } ;
struct flock {scalar_t__ l_len; scalar_t__ l_start; int /*<<< orphan*/  l_whence; int /*<<< orphan*/  l_type; } ;
struct TYPE_3__ {int last_open_time; int time_now; int interval; int /*<<< orphan*/ * backup; int /*<<< orphan*/  logname; } ;
typedef  TYPE_1__ ngx_pipe_rollback_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETLKW ; 
 int /*<<< orphan*/  F_WRLCK ; 
 int /*<<< orphan*/  NGX_FILE_OPEN ; 
 int /*<<< orphan*/  NGX_FILE_RDWR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  close (int) ; 
 int fcntl (int,int /*<<< orphan*/ ,struct flock*) ; 
 int ngx_file_info (int /*<<< orphan*/ ,struct stat*) ; 
 int ngx_open_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ngx_time () ; 

void ngx_pipe_get_last_rollback_time(ngx_pipe_rollback_conf_t *rbcf)
{
    int             fd;
    struct flock    lock;
    int             ret;

    struct stat     sb;

    fd = ngx_open_file(rbcf->logname, NGX_FILE_RDWR, NGX_FILE_OPEN, 0);
    if (fd < 0) {
        //open lock file failed just use now
        rbcf->last_open_time = rbcf->time_now;
        return;
    }

    lock.l_type     = F_WRLCK;
    lock.l_whence   = SEEK_SET;
    lock.l_start    = 0;
    lock.l_len      = 0;

    ret = fcntl(fd, F_SETLKW, &lock);
    if (ret < 0) {
        close(fd);
        //lock failed just use now
        rbcf->last_open_time = rbcf->time_now;
        return;
    }

    //check time
    if (rbcf->interval > 0) {
        if (ngx_file_info(rbcf->backup[0], &sb) == -1) {
            //no backup file ,so need rollback just set 1
            rbcf->last_open_time = 1;
        } else if (sb.st_ctime / rbcf->interval < ngx_time() / rbcf->interval) {
            //need rollback just set 1
            rbcf->last_open_time = 1;
        } else {
            //just no need rollback
            rbcf->last_open_time = rbcf->time_now;
        }
    } else {
        rbcf->last_open_time = rbcf->time_now;
    }

    close(fd);
}