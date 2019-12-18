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
struct scsi_id_device {char* serial; char* serial_short; char* wwn; char* wwn_vendor_extension; char* tgpt_group; char* unit_serial_number; } ;
typedef  int /*<<< orphan*/  serial_str ;

/* Variables and functions */
 int MAX_SERIAL_LEN ; 
 scalar_t__ export ; 
 char* model_enc_str ; 
 char* model_str ; 
 int /*<<< orphan*/  per_dev_options (struct scsi_id_device*,int*,int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ reformat_serial ; 
 char* revision_str ; 
 int /*<<< orphan*/  scsi_get_serial (struct scsi_id_device*,char*,int,int) ; 
 scalar_t__ set_inq_values (struct scsi_id_device*,char*) ; 
 char* type_str ; 
 int /*<<< orphan*/  util_replace_chars (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  util_replace_whitespace (char*,char*,int) ; 
 char* vendor_enc_str ; 
 char* vendor_str ; 

__attribute__((used)) static int scsi_id(char *maj_min_dev) {
        struct scsi_id_device dev_scsi = {};
        int good_dev;
        int page_code;
        int retval = 0;

        if (set_inq_values(&dev_scsi, maj_min_dev) < 0) {
                retval = 1;
                goto out;
        }

        /* get per device (vendor + model) options from the config file */
        per_dev_options(&dev_scsi, &good_dev, &page_code);
        if (!good_dev) {
                retval = 1;
                goto out;
        }

        /* read serial number from mode pages (no values for optical drives) */
        scsi_get_serial(&dev_scsi, maj_min_dev, page_code, MAX_SERIAL_LEN);

        if (export) {
                char serial_str[MAX_SERIAL_LEN];

                printf("ID_SCSI=1\n");
                printf("ID_VENDOR=%s\n", vendor_str);
                printf("ID_VENDOR_ENC=%s\n", vendor_enc_str);
                printf("ID_MODEL=%s\n", model_str);
                printf("ID_MODEL_ENC=%s\n", model_enc_str);
                printf("ID_REVISION=%s\n", revision_str);
                printf("ID_TYPE=%s\n", type_str);
                if (dev_scsi.serial[0] != '\0') {
                        util_replace_whitespace(dev_scsi.serial, serial_str, sizeof(serial_str)-1);
                        util_replace_chars(serial_str, NULL);
                        printf("ID_SERIAL=%s\n", serial_str);
                        util_replace_whitespace(dev_scsi.serial_short, serial_str, sizeof(serial_str)-1);
                        util_replace_chars(serial_str, NULL);
                        printf("ID_SERIAL_SHORT=%s\n", serial_str);
                }
                if (dev_scsi.wwn[0] != '\0') {
                        printf("ID_WWN=0x%s\n", dev_scsi.wwn);
                        if (dev_scsi.wwn_vendor_extension[0] != '\0') {
                                printf("ID_WWN_VENDOR_EXTENSION=0x%s\n", dev_scsi.wwn_vendor_extension);
                                printf("ID_WWN_WITH_EXTENSION=0x%s%s\n", dev_scsi.wwn, dev_scsi.wwn_vendor_extension);
                        } else
                                printf("ID_WWN_WITH_EXTENSION=0x%s\n", dev_scsi.wwn);
                }
                if (dev_scsi.tgpt_group[0] != '\0')
                        printf("ID_TARGET_PORT=%s\n", dev_scsi.tgpt_group);
                if (dev_scsi.unit_serial_number[0] != '\0')
                        printf("ID_SCSI_SERIAL=%s\n", dev_scsi.unit_serial_number);
                goto out;
        }

        if (dev_scsi.serial[0] == '\0') {
                retval = 1;
                goto out;
        }

        if (reformat_serial) {
                char serial_str[MAX_SERIAL_LEN];

                util_replace_whitespace(dev_scsi.serial, serial_str, sizeof(serial_str)-1);
                util_replace_chars(serial_str, NULL);
                printf("%s\n", serial_str);
                goto out;
        }

        printf("%s\n", dev_scsi.serial);
out:
        return retval;
}