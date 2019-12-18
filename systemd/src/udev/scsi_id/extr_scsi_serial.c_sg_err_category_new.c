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

/* Variables and functions */
 int /*<<< orphan*/  DID_BUS_BUSY ; 
 int /*<<< orphan*/  DID_NO_CONNECT ; 
 int /*<<< orphan*/  DID_TIME_OUT ; 
 int DRIVER_SENSE ; 
 int DRIVER_TIMEOUT ; 
 int ILLEGAL_REQUEST ; 
 scalar_t__ IN_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int RECOVERED_ERROR ; 
 int /*<<< orphan*/  SCSI_CHECK_CONDITION ; 
 int /*<<< orphan*/  SCSI_COMMAND_TERMINATED ; 
 int SG_ERR_CAT_CLEAN ; 
 int SG_ERR_CAT_MEDIA_CHANGED ; 
 int SG_ERR_CAT_NOTSUPPORTED ; 
 int SG_ERR_CAT_OTHER ; 
 int SG_ERR_CAT_RECOVERED ; 
 int SG_ERR_CAT_RESET ; 
 int SG_ERR_CAT_SENSE ; 
 int SG_ERR_CAT_TIMEOUT ; 
 int UNIT_ATTENTION ; 

__attribute__((used)) static int sg_err_category_new(int scsi_status, int msg_status, int
                               host_status, int driver_status, const
                               unsigned char *sense_buffer, int sb_len) {
        scsi_status &= 0x7e;

        /*
         * XXX change to return only two values - failed or OK.
         */

        if (!scsi_status && !host_status && !driver_status)
                return SG_ERR_CAT_CLEAN;

        if (IN_SET(scsi_status, SCSI_CHECK_CONDITION, SCSI_COMMAND_TERMINATED) ||
            (driver_status & 0xf) == DRIVER_SENSE) {
                if (sense_buffer && (sb_len > 2)) {
                        int sense_key;
                        unsigned char asc;

                        if (sense_buffer[0] & 0x2) {
                                sense_key = sense_buffer[1] & 0xf;
                                asc = sense_buffer[2];
                        } else {
                                sense_key = sense_buffer[2] & 0xf;
                                asc = (sb_len > 12) ? sense_buffer[12] : 0;
                        }

                        if (sense_key == RECOVERED_ERROR)
                                return SG_ERR_CAT_RECOVERED;
                        else if (sense_key == UNIT_ATTENTION) {
                                if (0x28 == asc)
                                        return SG_ERR_CAT_MEDIA_CHANGED;
                                if (0x29 == asc)
                                        return SG_ERR_CAT_RESET;
                        } else if (sense_key == ILLEGAL_REQUEST)
                                return SG_ERR_CAT_NOTSUPPORTED;
                }
                return SG_ERR_CAT_SENSE;
        }
        if (host_status) {
                if (IN_SET(host_status, DID_NO_CONNECT, DID_BUS_BUSY, DID_TIME_OUT))
                        return SG_ERR_CAT_TIMEOUT;
        }
        if (driver_status) {
                if (driver_status == DRIVER_TIMEOUT)
                        return SG_ERR_CAT_TIMEOUT;
        }
        return SG_ERR_CAT_OTHER;
}