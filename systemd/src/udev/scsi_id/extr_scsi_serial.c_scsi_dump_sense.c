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
struct scsi_id_device {int /*<<< orphan*/  kernel; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ IN_SET (int,int,int) ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ,int,...) ; 
 int log_debug_errno (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int scsi_dump_sense(struct scsi_id_device *dev_scsi,
                           unsigned char *sense_buffer, int sb_len) {
        int s;
        int code;
        int sense_class;
        int sense_key;
        int asc, ascq;

        /*
         * Figure out and print the sense key, asc and ascq.
         *
         * If you want to suppress these for a particular drive model, add
         * a black list entry in the scsi_id config file.
         *
         * XXX We probably need to: lookup the sense/asc/ascq in a retry
         * table, and if found return 1 (after dumping the sense, asc, and
         * ascq). So, if/when we get something like a power on/reset,
         * we'll retry the command.
         */

        if (sb_len < 1)
                return log_debug_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "%s: sense buffer empty",
                                       dev_scsi->kernel);

        sense_class = (sense_buffer[0] >> 4) & 0x07;
        code = sense_buffer[0] & 0xf;

        if (sense_class == 7) {
                /*
                 * extended sense data.
                 */
                s = sense_buffer[7] + 8;
                if (sb_len < s)
                        return log_debug_errno(SYNTHETIC_ERRNO(EINVAL),
                                               "%s: sense buffer too small %d bytes, %d bytes too short",
                                               dev_scsi->kernel, sb_len,
                                               s - sb_len);

                if (IN_SET(code, 0x0, 0x1)) {
                        sense_key = sense_buffer[2] & 0xf;
                        if (s < 14)
                                /*
                                 * Possible?
                                 */
                                return log_debug_errno(SYNTHETIC_ERRNO(EINVAL),
                                                       "%s: sense result too small %d bytes",
                                                       dev_scsi->kernel, s);

                        asc = sense_buffer[12];
                        ascq = sense_buffer[13];
                } else if (IN_SET(code, 0x2, 0x3)) {
                        sense_key = sense_buffer[1] & 0xf;
                        asc = sense_buffer[2];
                        ascq = sense_buffer[3];
                } else
                        return log_debug_errno(SYNTHETIC_ERRNO(EINVAL),
                                               "%s: invalid sense code 0x%x",
                                               dev_scsi->kernel, code);

                log_debug("%s: sense key 0x%x ASC 0x%x ASCQ 0x%x",
                          dev_scsi->kernel, sense_key, asc, ascq);
        } else {
                if (sb_len < 4)
                        return log_debug_errno(SYNTHETIC_ERRNO(EINVAL),
                                               "%s: sense buffer too small %d bytes, %d bytes too short",
                                               dev_scsi->kernel, sb_len,
                                               4 - sb_len);

                if (sense_buffer[0] < 15)
                        log_debug("%s: old sense key: 0x%x", dev_scsi->kernel, sense_buffer[0] & 0x0f);
                else
                        log_debug("%s: sense = %2x %2x",
                                  dev_scsi->kernel, sense_buffer[0], sense_buffer[2]);
                log_debug("%s: non-extended sense class %d code 0x%0x",
                          dev_scsi->kernel, sense_class, code);

        }

        return -1;
}