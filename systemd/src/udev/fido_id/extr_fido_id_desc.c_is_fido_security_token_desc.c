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
typedef  int uint32_t ;

/* Variables and functions */
 int EINVAL ; 
 int FIDO_FULL_USAGE_CTAPHID ; 
 int const HID_RPTDESC_FIRST_BYTE_LONG_ITEM ; 
 int HID_RPTDESC_TAG_USAGE ; 
 int HID_RPTDESC_TAG_USAGE_PAGE ; 
 int HID_RPTDESC_TYPE_GLOBAL ; 
 int HID_RPTDESC_TYPE_LOCAL ; 

int is_fido_security_token_desc(const uint8_t *desc, size_t desc_len) {
        uint32_t usage = 0;

        for (size_t pos = 0; pos < desc_len; ) {
                uint8_t tag, type, size_code;
                size_t size;
                uint32_t value;

                /* Report descriptors consists of short items (1-5 bytes) and long items (3-258 bytes). */
                if (desc[pos] == HID_RPTDESC_FIRST_BYTE_LONG_ITEM) {
                        /* No long items are defined in the spec; skip them.
                         * The length of the data in a long item is contained in the byte after the long
                         * item tag. The header consists of three bytes: special long item tag, length,
                         * actual tag. */
                        if (pos + 1 >= desc_len)
                                return -EINVAL;
                        pos += desc[pos + 1] + 3;
                        continue;
                }

                /* The first byte of a short item encodes tag, type and size. */
                tag = desc[pos] >> 4;          /* Bits 7 to 4 */
                type = (desc[pos] >> 2) & 0x3; /* Bits 3 and 2 */
                size_code = desc[pos] & 0x3;   /* Bits 1 and 0 */
                /* Size is coded as follows:
                 * 0 -> 0 bytes, 1 -> 1 byte, 2 -> 2 bytes, 3 -> 4 bytes
                 */
                size = size_code < 3 ? size_code : 4;
                /* Consume header byte. */
                pos++;

                /* Extract the item value coded on size bytes. */
                if (pos + size > desc_len)
                        return -EINVAL;
                value = 0;
                for (size_t i = 0; i < size; i++)
                        value |= (uint32_t) desc[pos + i] << (8 * i);
                /* Consume value bytes. */
                pos += size;

                if (type == HID_RPTDESC_TYPE_GLOBAL && tag == HID_RPTDESC_TAG_USAGE_PAGE) {
                        /* A usage page is a 16 bit value coded on at most 16 bits. */
                        if (size > 2)
                                return -EINVAL;
                        /* A usage page sets the upper 16 bits of a following usage. */
                        usage = (value & 0x0000ffffu) << 16;
                }

                if (type == HID_RPTDESC_TYPE_LOCAL && tag == HID_RPTDESC_TAG_USAGE) {
                        /* A usage is a 32 bit value, but is prepended with the current usage page if
                         * coded on less than 4 bytes (that is, at most 2 bytes). */
                        if (size == 4)
                                usage = value;
                        else
                                usage = (usage & 0xffff0000u) | (value & 0x0000ffffu);
                        if (usage == FIDO_FULL_USAGE_CTAPHID)
                                return 1;
                }
        }

        return 0;
}