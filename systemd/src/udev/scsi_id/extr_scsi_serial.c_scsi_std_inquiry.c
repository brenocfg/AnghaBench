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
struct stat {int /*<<< orphan*/  st_rdev; } ;
struct scsi_id_device {char* vendor; char* model; char* revision; int /*<<< orphan*/  type; int /*<<< orphan*/  kernel; } ;

/* Variables and functions */
 int O_CLOEXEC ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int SCSI_INQ_BUFF_LEN ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  log_debug_errno (int /*<<< orphan*/ ,char*,char const*) ; 
 int major (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memzero (unsigned char*,int) ; 
 int minor (int /*<<< orphan*/ ) ; 
 int open (char const*,int) ; 
 int scsi_inquiry (struct scsi_id_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,unsigned char,...) ; 

int scsi_std_inquiry(struct scsi_id_device *dev_scsi, const char *devname) {
        int fd;
        unsigned char buf[SCSI_INQ_BUFF_LEN];
        struct stat statbuf;
        int err = 0;

        fd = open(devname, O_RDONLY | O_NONBLOCK | O_CLOEXEC);
        if (fd < 0) {
                log_debug_errno(errno, "scsi_id: cannot open %s: %m", devname);
                return 1;
        }

        if (fstat(fd, &statbuf) < 0) {
                log_debug_errno(errno, "scsi_id: cannot stat %s: %m", devname);
                err = 2;
                goto out;
        }
        sprintf(dev_scsi->kernel,"%d:%d", major(statbuf.st_rdev),
                minor(statbuf.st_rdev));

        memzero(buf, SCSI_INQ_BUFF_LEN);
        err = scsi_inquiry(dev_scsi, fd, 0, 0, buf, SCSI_INQ_BUFF_LEN);
        if (err < 0)
                goto out;

        err = 0;
        memcpy(dev_scsi->vendor, buf + 8, 8);
        dev_scsi->vendor[8] = '\0';
        memcpy(dev_scsi->model, buf + 16, 16);
        dev_scsi->model[16] = '\0';
        memcpy(dev_scsi->revision, buf + 32, 4);
        dev_scsi->revision[4] = '\0';
        sprintf(dev_scsi->type,"%x", buf[0] & 0x1f);

out:
        close(fd);
        return err;
}