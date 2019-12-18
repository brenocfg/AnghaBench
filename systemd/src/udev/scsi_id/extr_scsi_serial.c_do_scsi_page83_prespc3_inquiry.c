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
 unsigned char PAGE_83 ; 
 size_t SCSI_ID_NAA ; 
 int SCSI_INQ_BUFF_LEN ; 
 char* hex_str ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memzero (unsigned char*,int) ; 
 int scsi_inquiry (struct scsi_id_device*,int,int,unsigned char,unsigned char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static int do_scsi_page83_prespc3_inquiry(struct scsi_id_device *dev_scsi, int fd,
                                          char *serial, char *serial_short, int len) {
        int retval;
        int i, j;
        unsigned char page_83[SCSI_INQ_BUFF_LEN];

        memzero(page_83, SCSI_INQ_BUFF_LEN);
        retval = scsi_inquiry(dev_scsi, fd, 1, PAGE_83, page_83, SCSI_INQ_BUFF_LEN);
        if (retval < 0)
                return 1;

        if (page_83[1] != PAGE_83) {
                log_debug("%s: Invalid page 0x83", dev_scsi->kernel);
                return 1;
        }
        /*
         * Model 4, 5, and (some) model 6 EMC Symmetrix devices return
         * a page 83 reply according to SCSI-2 format instead of SPC-2/3.
         *
         * The SCSI-2 page 83 format returns an IEEE WWN in binary
         * encoded hexi-decimal in the 16 bytes following the initial
         * 4-byte page 83 reply header.
         *
         * Both the SPC-2 and SPC-3 formats return an IEEE WWN as part
         * of an Identification descriptor.  The 3rd byte of the first
         * Identification descriptor is a reserved (BSZ) byte field.
         *
         * Reference the 7th byte of the page 83 reply to determine
         * whether the reply is compliant with SCSI-2 or SPC-2/3
         * specifications.  A zero value in the 7th byte indicates
         * an SPC-2/3 conformant reply, (i.e., the reserved field of the
         * first Identification descriptor).  This byte will be non-zero
         * for a SCSI-2 conformant page 83 reply from these EMC
         * Symmetrix models since the 7th byte of the reply corresponds
         * to the 4th and 5th nibbles of the 6-byte OUI for EMC, that is,
         * 0x006048.
         */
        if (page_83[6] == 0)
                return 2;

        serial[0] = hex_str[SCSI_ID_NAA];
        /*
         * The first four bytes contain data, not a descriptor.
         */
        i = 4;
        j = strlen(serial);
        /*
         * Binary descriptor, convert to ASCII,
         * using two bytes of ASCII for each byte
         * in the page_83.
         */
        while (i < (page_83[3]+4)) {
                serial[j++] = hex_str[(page_83[i] & 0xf0) >> 4];
                serial[j++] = hex_str[page_83[i] & 0x0f];
                i++;
        }
        return 0;
}