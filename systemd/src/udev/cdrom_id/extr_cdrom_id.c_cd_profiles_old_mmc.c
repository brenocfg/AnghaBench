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
typedef  int /*<<< orphan*/  header ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEDIUM ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 scalar_t__ cd_cd_r ; 
 int cd_media ; 
 int cd_media_cd_r ; 
 int cd_media_cd_rom ; 
 int cd_media_cd_rw ; 
 int cd_media_track_count ; 
 int cd_media_track_count_data ; 
 int /*<<< orphan*/  info_scsi_cmd_err (char*,int) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int log_debug_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  scsi_cmd_init (struct scsi_cmd*) ; 
 int scsi_cmd_run (struct scsi_cmd*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  scsi_cmd_set (struct scsi_cmd*,int,int) ; 

__attribute__((used)) static int cd_profiles_old_mmc(int fd) {
        struct scsi_cmd sc;
        int err;

        unsigned char header[32];

        scsi_cmd_init(&sc);
        scsi_cmd_set(&sc, 0, 0x51);
        scsi_cmd_set(&sc, 8, sizeof(header));
        scsi_cmd_set(&sc, 9, 0);
        err = scsi_cmd_run(&sc, fd, header, sizeof(header));
        if (err != 0) {
                info_scsi_cmd_err("READ DISC INFORMATION", err);
                if (cd_media == 1) {
                        log_debug("no current profile, but disc is present; assuming CD-ROM");
                        cd_media_cd_rom = 1;
                        cd_media_track_count = 1;
                        cd_media_track_count_data = 1;
                        return 0;
                } else
                        return log_debug_errno(SYNTHETIC_ERRNO(ENOMEDIUM),
                                               "no current profile, assuming no media");
        };

        cd_media = 1;

        if (header[2] & 16) {
                cd_media_cd_rw = 1;
                log_debug("profile 0x0a media_cd_rw");
        } else if ((header[2] & 3) < 2 && cd_cd_r) {
                cd_media_cd_r = 1;
                log_debug("profile 0x09 media_cd_r");
        } else {
                cd_media_cd_rom = 1;
                log_debug("profile 0x08 media_cd_rom");
        }
        return 0;
}