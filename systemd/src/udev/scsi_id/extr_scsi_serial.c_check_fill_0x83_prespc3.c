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
struct scsi_id_search_values {int dummy; } ;
struct scsi_id_device {int dummy; } ;

/* Variables and functions */
 size_t SCSI_ID_NAA ; 
 char* hex_str ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static int check_fill_0x83_prespc3(struct scsi_id_device *dev_scsi,
                                   unsigned char *page_83,
                                   const struct scsi_id_search_values
                                   *id_search, char *serial, char *serial_short, int max_len) {
        int i, j;

        serial[0] = hex_str[SCSI_ID_NAA];
        /* serial has been memset to zero before */
        j = strlen(serial);        /* j = 1; */

        for (i = 0; (i < page_83[3]) && (j < max_len-3); ++i) {
                serial[j++] = hex_str[(page_83[4+i] & 0xf0) >> 4];
                serial[j++] = hex_str[ page_83[4+i] & 0x0f];
        }
        serial[max_len-1] = 0;
        strncpy(serial_short, serial, max_len-1);
        return 0;
}