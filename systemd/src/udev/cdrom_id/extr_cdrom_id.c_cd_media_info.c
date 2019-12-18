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
typedef  int /*<<< orphan*/  format ;
typedef  int /*<<< orphan*/  dvdstruct ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEDIUM ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int cd_media ; 
 int /*<<< orphan*/  cd_media_cd_rom ; 
 scalar_t__ cd_media_dvd_plus_rw ; 
 scalar_t__ cd_media_dvd_plus_rw_dl ; 
 scalar_t__ cd_media_dvd_ram ; 
 scalar_t__ cd_media_dvd_rw_ro ; 
 unsigned char cd_media_session_count ; 
 unsigned char cd_media_session_next ; 
 char* cd_media_state ; 
 unsigned char cd_media_track_count ; 
 int /*<<< orphan*/  info_scsi_cmd_err (char*,int) ; 
 int /*<<< orphan*/  log_debug (char*,...) ; 
 int log_debug_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  scsi_cmd_init (struct scsi_cmd*) ; 
 int scsi_cmd_run (struct scsi_cmd*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  scsi_cmd_set (struct scsi_cmd*,int,int) ; 

__attribute__((used)) static int cd_media_info(int fd) {
        struct scsi_cmd sc;
        unsigned char header[32];
        static const char *const media_status[] = {
                "blank",
                "appendable",
                "complete",
                "other"
        };
        int err;

        scsi_cmd_init(&sc);
        scsi_cmd_set(&sc, 0, 0x51);
        scsi_cmd_set(&sc, 8, sizeof(header) & 0xff);
        scsi_cmd_set(&sc, 9, 0);
        err = scsi_cmd_run(&sc, fd, header, sizeof(header));
        if (err != 0) {
                info_scsi_cmd_err("READ DISC INFORMATION", err);
                return -1;
        };

        cd_media = 1;
        log_debug("disk type %02x", header[8]);
        log_debug("hardware reported media status: %s", media_status[header[2] & 3]);

        /* exclude plain CDROM, some fake cdroms return 0 for "blank" media here */
        if (!cd_media_cd_rom)
                cd_media_state = media_status[header[2] & 3];

        /* fresh DVD-RW in restricted overwrite mode reports itself as
         * "appendable"; change it to "blank" to make it consistent with what
         * gets reported after blanking, and what userspace expects  */
        if (cd_media_dvd_rw_ro && (header[2] & 3) == 1)
                cd_media_state = media_status[0];

        /* DVD+RW discs (and DVD-RW in restricted mode) once formatted are
         * always "complete", DVD-RAM are "other" or "complete" if the disc is
         * write protected; we need to check the contents if it is blank */
        if ((cd_media_dvd_rw_ro || cd_media_dvd_plus_rw || cd_media_dvd_plus_rw_dl || cd_media_dvd_ram) && (header[2] & 3) > 1) {
                unsigned char buffer[32 * 2048];
                unsigned char len;
                int offset;

                if (cd_media_dvd_ram) {
                        /* a write protected dvd-ram may report "complete" status */

                        unsigned char dvdstruct[8];
                        unsigned char format[12];

                        scsi_cmd_init(&sc);
                        scsi_cmd_set(&sc, 0, 0xAD);
                        scsi_cmd_set(&sc, 7, 0xC0);
                        scsi_cmd_set(&sc, 9, sizeof(dvdstruct));
                        scsi_cmd_set(&sc, 11, 0);
                        err = scsi_cmd_run(&sc, fd, dvdstruct, sizeof(dvdstruct));
                        if (err != 0) {
                                info_scsi_cmd_err("READ DVD STRUCTURE", err);
                                return -1;
                        }
                        if (dvdstruct[4] & 0x02) {
                                cd_media_state = media_status[2];
                                log_debug("write-protected DVD-RAM media inserted");
                                goto determined;
                        }

                        /* let's make sure we don't try to read unformatted media */
                        scsi_cmd_init(&sc);
                        scsi_cmd_set(&sc, 0, 0x23);
                        scsi_cmd_set(&sc, 8, sizeof(format));
                        scsi_cmd_set(&sc, 9, 0);
                        err = scsi_cmd_run(&sc, fd, format, sizeof(format));
                        if (err != 0) {
                                info_scsi_cmd_err("READ DVD FORMAT CAPACITIES", err);
                                return -1;
                        }

                        len = format[3];
                        if (len & 7 || len < 16)
                                return log_debug_errno(SYNTHETIC_ERRNO(EINVAL),
                                                       "invalid format capacities length");

                        switch(format[8] & 3) {
                            case 1:
                                log_debug("unformatted DVD-RAM media inserted");
                                /* This means that last format was interrupted
                                 * or failed, blank dvd-ram discs are factory
                                 * formatted. Take no action here as it takes
                                 * quite a while to reformat a dvd-ram and it's
                                 * not automatically started */
                                goto determined;

                            case 2:
                                log_debug("formatted DVD-RAM media inserted");
                                break;

                            case 3:
                                cd_media = 0; //return no media
                                return log_debug_errno(SYNTHETIC_ERRNO(ENOMEDIUM),
                                                       "format capacities returned no media");
                        }
                }

                /* Take a closer look at formatted media (unformatted DVD+RW
                 * has "blank" status", DVD-RAM was examined earlier) and check
                 * for ISO and UDF PVDs or a fs superblock presence and do it
                 * in one ioctl (we need just sectors 0 and 16) */
                scsi_cmd_init(&sc);
                scsi_cmd_set(&sc, 0, 0x28);
                scsi_cmd_set(&sc, 5, 0);
                scsi_cmd_set(&sc, 8, 32);
                scsi_cmd_set(&sc, 9, 0);
                err = scsi_cmd_run(&sc, fd, buffer, sizeof(buffer));
                if (err != 0) {
                        cd_media = 0;
                        info_scsi_cmd_err("READ FIRST 32 BLOCKS", err);
                        return -1;
                }

                /* if any non-zero data is found in sector 16 (iso and udf) or
                 * eventually 0 (fat32 boot sector, ext2 superblock, etc), disc
                 * is assumed non-blank */

                for (offset = 32768; offset < (32768 + 2048); offset++) {
                        if (buffer [offset]) {
                                log_debug("data in block 16, assuming complete");
                                goto determined;
                        }
                }

                for (offset = 0; offset < 2048; offset++) {
                        if (buffer [offset]) {
                                log_debug("data in block 0, assuming complete");
                                goto determined;
                        }
                }

                cd_media_state = media_status[0];
                log_debug("no data in blocks 0 or 16, assuming blank");
        }

determined:
        /* "other" is e. g. DVD-RAM, can't append sessions there; DVDs in
         * restricted overwrite mode can never append, only in sequential mode */
        if ((header[2] & 3) < 2 && !cd_media_dvd_rw_ro)
                cd_media_session_next = header[10] << 8 | header[5];
        cd_media_session_count = header[9] << 8 | header[4];
        cd_media_track_count = header[11] << 8 | header[6];

        return 0;
}