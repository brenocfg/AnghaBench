#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char interface_id; int mx_sb_len; int flags; int /*<<< orphan*/  sbp; int /*<<< orphan*/  cmdp; } ;
struct TYPE_4__ {int /*<<< orphan*/  u; int /*<<< orphan*/  s; } ;
struct TYPE_6__ {int quiet; int /*<<< orphan*/  cmd; int /*<<< orphan*/ * sense; } ;
struct scsi_cmd {TYPE_2__ sg_io; TYPE_1__ _sense; TYPE_3__ cgc; } ;

/* Variables and functions */
 int SG_FLAG_DIRECT_IO ; 
 int SG_FLAG_LUN_INHIBIT ; 
 int /*<<< orphan*/  memzero (struct scsi_cmd*,int) ; 

__attribute__((used)) static void scsi_cmd_init(struct scsi_cmd *cmd) {
        memzero(cmd, sizeof(struct scsi_cmd));
        cmd->cgc.quiet = 1;
        cmd->cgc.sense = &cmd->_sense.s;
        cmd->sg_io.interface_id = 'S';
        cmd->sg_io.mx_sb_len = sizeof(cmd->_sense);
        cmd->sg_io.cmdp = cmd->cgc.cmd;
        cmd->sg_io.sbp = cmd->_sense.u;
        cmd->sg_io.flags = SG_FLAG_LUN_INHIBIT | SG_FLAG_DIRECT_IO;
}