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
struct scsi_id_search_values {unsigned char id_type; unsigned char naa_type; unsigned char code_set; } ;
struct scsi_id_device {int /*<<< orphan*/  kernel; } ;

/* Variables and functions */
 scalar_t__ MODEL_LENGTH ; 
 unsigned char SCSI_ID_ASCII ; 
 unsigned char SCSI_ID_NAA ; 
 unsigned char SCSI_ID_NAA_DONT_CARE ; 
 unsigned char SCSI_ID_TGTGROUP ; 
 unsigned char SCSI_ID_VENDOR_SPECIFIC ; 
 scalar_t__ VENDOR_LENGTH ; 
 scalar_t__ append_vendor_model (struct scsi_id_device*,char*) ; 
 char* hex_str ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static int check_fill_0x83_id(struct scsi_id_device *dev_scsi,
                              unsigned char *page_83,
                              const struct scsi_id_search_values
                              *id_search, char *serial, char *serial_short,
                              int max_len, char *wwn,
                              char *wwn_vendor_extension, char *tgpt_group) {
        int i, j, s, len;

        /*
         * ASSOCIATION must be with the device (value 0)
         * or with the target port for SCSI_ID_TGTPORT
         */
        if ((page_83[1] & 0x30) == 0x10) {
                if (id_search->id_type != SCSI_ID_TGTGROUP)
                        return 1;
        } else if ((page_83[1] & 0x30) != 0)
                return 1;

        if ((page_83[1] & 0x0f) != id_search->id_type)
                return 1;

        /*
         * Possibly check NAA sub-type.
         */
        if ((id_search->naa_type != SCSI_ID_NAA_DONT_CARE) &&
            (id_search->naa_type != (page_83[4] & 0xf0) >> 4))
                return 1;

        /*
         * Check for matching code set - ASCII or BINARY.
         */
        if ((page_83[0] & 0x0f) != id_search->code_set)
                return 1;

        /*
         * page_83[3]: identifier length
         */
        len = page_83[3];
        if ((page_83[0] & 0x0f) != SCSI_ID_ASCII)
                /*
                 * If not ASCII, use two bytes for each binary value.
                 */
                len *= 2;

        /*
         * Add one byte for the NUL termination, and one for the id_type.
         */
        len += 2;
        if (id_search->id_type == SCSI_ID_VENDOR_SPECIFIC)
                len += VENDOR_LENGTH + MODEL_LENGTH;

        if (max_len < len) {
                log_debug("%s: length %d too short - need %d",
                          dev_scsi->kernel, max_len, len);
                return 1;
        }

        if (id_search->id_type == SCSI_ID_TGTGROUP && tgpt_group != NULL) {
                unsigned group;

                group = ((unsigned)page_83[6] << 8) | page_83[7];
                sprintf(tgpt_group,"%x", group);
                return 1;
        }

        serial[0] = hex_str[id_search->id_type];

        /*
         * For SCSI_ID_VENDOR_SPECIFIC prepend the vendor and model before
         * the id since it is not unique across all vendors and models,
         * this differs from SCSI_ID_T10_VENDOR, where the vendor is
         * included in the identifier.
         */
        if (id_search->id_type == SCSI_ID_VENDOR_SPECIFIC)
                if (append_vendor_model(dev_scsi, serial + 1) < 0)
                        return 1;

        i = 4; /* offset to the start of the identifier */
        s = j = strlen(serial);
        if ((page_83[0] & 0x0f) == SCSI_ID_ASCII) {
                /*
                 * ASCII descriptor.
                 */
                while (i < (4 + page_83[3]))
                        serial[j++] = page_83[i++];
        } else {
                /*
                 * Binary descriptor, convert to ASCII, using two bytes of
                 * ASCII for each byte in the page_83.
                 */
                while (i < (4 + page_83[3])) {
                        serial[j++] = hex_str[(page_83[i] & 0xf0) >> 4];
                        serial[j++] = hex_str[page_83[i] & 0x0f];
                        i++;
                }
        }

        strcpy(serial_short, serial + s);

        if (id_search->id_type == SCSI_ID_NAA && wwn != NULL) {
                strncpy(wwn, serial + s, 16);
                if (wwn_vendor_extension)
                        strncpy(wwn_vendor_extension, serial + s + 16, 16);
        }

        return 0;
}