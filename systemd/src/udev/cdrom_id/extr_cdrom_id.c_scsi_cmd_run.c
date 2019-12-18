#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  u; } ;
struct TYPE_4__ {unsigned char* dxferp; size_t dxfer_len; int info; int masked_status; int /*<<< orphan*/  dxfer_direction; } ;
struct scsi_cmd {TYPE_1__ _sense; TYPE_2__ sg_io; } ;

/* Variables and functions */
 int CHECK_CONDITION ; 
 int /*<<< orphan*/  EIO ; 
 int ERRCODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SG_DXFER_FROM_DEV ; 
 int /*<<< orphan*/  SG_DXFER_NONE ; 
 int SG_INFO_OK ; 
 int SG_INFO_OK_MASK ; 
 int /*<<< orphan*/  SG_IO ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int scsi_cmd_run(struct scsi_cmd *cmd, int fd, unsigned char *buf, size_t bufsize) {
        int ret = 0;

        if (bufsize > 0) {
                cmd->sg_io.dxferp = buf;
                cmd->sg_io.dxfer_len = bufsize;
                cmd->sg_io.dxfer_direction = SG_DXFER_FROM_DEV;
        } else
                cmd->sg_io.dxfer_direction = SG_DXFER_NONE;

        if (ioctl(fd, SG_IO, &cmd->sg_io))
                return -1;

        if ((cmd->sg_io.info & SG_INFO_OK_MASK) != SG_INFO_OK) {
                errno = EIO;
                ret = -1;
                if (cmd->sg_io.masked_status & CHECK_CONDITION) {
                        ret = ERRCODE(cmd->_sense.u);
                        if (ret == 0)
                                ret = -1;
                }
        }
        return ret;
}