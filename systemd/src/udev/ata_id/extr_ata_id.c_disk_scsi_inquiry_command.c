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
struct sg_io_v4 {char guard; int request_len; uintptr_t request; int max_response_len; uintptr_t response; size_t din_xfer_len; uintptr_t din_xferp; char interface_id; unsigned char* cmdp; int cmd_len; void* dxferp; size_t dxfer_len; int* sbp; int mx_sb_len; scalar_t__ status; scalar_t__ host_status; scalar_t__ driver_status; scalar_t__ device_status; scalar_t__ transport_status; int /*<<< orphan*/  timeout; int /*<<< orphan*/  dxfer_direction; int /*<<< orphan*/  subprotocol; int /*<<< orphan*/  protocol; } ;
struct sg_io_hdr {char guard; int request_len; uintptr_t request; int max_response_len; uintptr_t response; size_t din_xfer_len; uintptr_t din_xferp; char interface_id; unsigned char* cmdp; int cmd_len; void* dxferp; size_t dxfer_len; int* sbp; int mx_sb_len; scalar_t__ status; scalar_t__ host_status; scalar_t__ driver_status; scalar_t__ device_status; scalar_t__ transport_status; int /*<<< orphan*/  timeout; int /*<<< orphan*/  dxfer_direction; int /*<<< orphan*/  subprotocol; int /*<<< orphan*/  protocol; } ;
typedef  int /*<<< orphan*/  sense ;
typedef  int /*<<< orphan*/  cdb ;

/* Variables and functions */
 int /*<<< orphan*/  BSG_PROTOCOL_SCSI ; 
 int /*<<< orphan*/  BSG_SUB_PROTOCOL_SCSI_CMD ; 
 int /*<<< orphan*/  COMMAND_TIMEOUT_MSEC ; 
 scalar_t__ EINVAL ; 
 scalar_t__ EIO ; 
 int /*<<< orphan*/  SG_DXFER_FROM_DEV ; 
 int /*<<< orphan*/  SG_IO ; 
 scalar_t__ errno ; 
 int ioctl (int,int /*<<< orphan*/ ,struct sg_io_v4*) ; 

__attribute__((used)) static int disk_scsi_inquiry_command(
                int fd,
                void *buf,
                size_t buf_len) {

        uint8_t cdb[6] = {
                /* INQUIRY, see SPC-4 section 6.4 */
                [0] = 0x12,                /* OPERATION CODE: INQUIRY */
                [3] = (buf_len >> 8),      /* ALLOCATION LENGTH */
                [4] = (buf_len & 0xff),
        };
        uint8_t sense[32] = {};
        struct sg_io_v4 io_v4 = {
                .guard = 'Q',
                .protocol = BSG_PROTOCOL_SCSI,
                .subprotocol = BSG_SUB_PROTOCOL_SCSI_CMD,
                .request_len = sizeof(cdb),
                .request = (uintptr_t) cdb,
                .max_response_len = sizeof(sense),
                .response = (uintptr_t) sense,
                .din_xfer_len = buf_len,
                .din_xferp = (uintptr_t) buf,
                .timeout = COMMAND_TIMEOUT_MSEC,
        };
        int ret;

        ret = ioctl(fd, SG_IO, &io_v4);
        if (ret != 0) {
                /* could be that the driver doesn't do version 4, try version 3 */
                if (errno == EINVAL) {
                        struct sg_io_hdr io_hdr = {
                                .interface_id = 'S',
                                .cmdp = (unsigned char*) cdb,
                                .cmd_len = sizeof (cdb),
                                .dxferp = buf,
                                .dxfer_len = buf_len,
                                .sbp = sense,
                                .mx_sb_len = sizeof(sense),
                                .dxfer_direction = SG_DXFER_FROM_DEV,
                                .timeout = COMMAND_TIMEOUT_MSEC,
                        };

                        ret = ioctl(fd, SG_IO, &io_hdr);
                        if (ret != 0)
                                return ret;

                        /* even if the ioctl succeeds, we need to check the return value */
                        if (!(io_hdr.status == 0 &&
                              io_hdr.host_status == 0 &&
                              io_hdr.driver_status == 0)) {
                                errno = EIO;
                                return -1;
                        }
                } else
                        return ret;
        }

        /* even if the ioctl succeeds, we need to check the return value */
        if (!(io_v4.device_status == 0 &&
              io_v4.transport_status == 0 &&
              io_v4.driver_status == 0)) {
                errno = EIO;
                return -1;
        }

        return 0;
}