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
struct scsi_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  info_scsi_cmd_err (char*,int) ; 
 int /*<<< orphan*/  log_debug (char*,unsigned char*,unsigned char*,unsigned char*) ; 
 int log_debug_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  scsi_cmd_init (struct scsi_cmd*) ; 
 int scsi_cmd_run (struct scsi_cmd*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  scsi_cmd_set (struct scsi_cmd*,int,int) ; 

__attribute__((used)) static int cd_inquiry(int fd) {
        struct scsi_cmd sc;
        unsigned char inq[128];
        int err;

        scsi_cmd_init(&sc);
        scsi_cmd_set(&sc, 0, 0x12);
        scsi_cmd_set(&sc, 4, 36);
        scsi_cmd_set(&sc, 5, 0);
        err = scsi_cmd_run(&sc, fd, inq, 36);
        if (err != 0) {
                info_scsi_cmd_err("INQUIRY", err);
                return -1;
        }

        if ((inq[0] & 0x1F) != 5)
                return log_debug_errno(SYNTHETIC_ERRNO(EINVAL), "not an MMC unit");

        log_debug("INQUIRY: [%.8s][%.16s][%.4s]", inq + 8, inq + 16, inq + 32);
        return 0;
}