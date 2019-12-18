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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  inquiry_buf ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int disk_identify_command (int,int*,int) ; 
 int disk_identify_packet_device_command (int,int*,int) ; 
 int disk_scsi_inquiry_command (int,int*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memzero (int*,int) ; 

__attribute__((used)) static int disk_identify(int fd,
                         uint8_t out_identify[512],
                         int *out_is_packet_device) {
        int ret;
        uint8_t inquiry_buf[36];
        int peripheral_device_type;
        int all_nul_bytes;
        int n;
        int is_packet_device = 0;

        /* init results */
        memzero(out_identify, 512);

        /* If we were to use ATA PASS_THROUGH (12) on an ATAPI device
         * we could accidentally blank media. This is because MMC's BLANK
         * command has the same op-code (0x61).
         *
         * To prevent this from happening we bail out if the device
         * isn't a Direct Access Block Device, e.g. SCSI type 0x00
         * (CD/DVD devices are type 0x05). So we send a SCSI INQUIRY
         * command first... libata is handling this via its SCSI
         * emulation layer.
         *
         * This also ensures that we're actually dealing with a device
         * that understands SCSI commands.
         *
         * (Yes, it is a bit perverse that we're tunneling the ATA
         * command through SCSI and relying on the ATA driver
         * emulating SCSI well-enough...)
         *
         * (See commit 160b069c25690bfb0c785994c7c3710289179107 for
         * the original bug-fix and see http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=556635
         * for the original bug-report.)
         */
        ret = disk_scsi_inquiry_command (fd, inquiry_buf, sizeof (inquiry_buf));
        if (ret != 0)
                goto out;

        /* SPC-4, section 6.4.2: Standard INQUIRY data */
        peripheral_device_type = inquiry_buf[0] & 0x1f;
        if (peripheral_device_type == 0x05)
          {
            is_packet_device = 1;
            ret = disk_identify_packet_device_command(fd, out_identify, 512);
            goto check_nul_bytes;
          }
        if (peripheral_device_type != 0x00) {
                ret = -1;
                errno = EIO;
                goto out;
        }

        /* OK, now issue the IDENTIFY DEVICE command */
        ret = disk_identify_command(fd, out_identify, 512);
        if (ret != 0)
                goto out;

 check_nul_bytes:
         /* Check if IDENTIFY data is all NUL bytes - if so, bail */
        all_nul_bytes = 1;
        for (n = 0; n < 512; n++) {
                if (out_identify[n] != '\0') {
                        all_nul_bytes = 0;
                        break;
                }
        }

        if (all_nul_bytes) {
                ret = -1;
                errno = EIO;
                goto out;
        }

out:
        if (out_is_packet_device)
                *out_is_packet_device = is_packet_device;
        return ret;
}