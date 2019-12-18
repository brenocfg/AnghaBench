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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  Check (int) ; 
 int /*<<< orphan*/  ar_conv_rune_to_utf8 (char const,char*,int) ; 
 char* calloc (int,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *rar_conv_unicode_to_utf8(const char *data, uint16_t len)
{
#define Check(cond) if (!(cond)) { free(str); return NULL; } else ((void)0)

    uint8_t highbyte, flagbyte, flagbits, size, length, i;
    const uint8_t *in = (uint8_t *)data + strlen(data) + 1;
    const uint8_t *end_in = (uint8_t *)data + len;
    char *str = calloc(len + 1, 3);
    char *out = str;
    char *end_out = str + len * 3;

    if (!str)
        return NULL;
    if (end_in - in <= 1) {
        memcpy(str, data, len);
        return str;
    }

    highbyte = *in++;
    flagbyte = 0;
    flagbits = 0;
    size = 0;

    while (in < end_in && out < end_out) {
        if (flagbits == 0) {
            flagbyte = *in++;
            flagbits = 8;
        }
        flagbits -= 2;
        switch ((flagbyte >> flagbits) & 3) {
        case 0:
            Check(in + 1 <= end_in);
            out += ar_conv_rune_to_utf8(*in++, out, end_out - out);
            size++;
            break;
        case 1:
            Check(in + 1 <= end_in);
            out += ar_conv_rune_to_utf8(((uint16_t)highbyte << 8) | *in++, out, end_out - out);
            size++;
            break;
        case 2:
            Check(in + 2 <= end_in);
            out += ar_conv_rune_to_utf8(((uint16_t)*(in + 1) << 8) | *in, out, end_out - out);
            in += 2;
            size++;
            break;
        case 3:
            Check(in + 1 <= end_in);
            length = *in++;
            if ((length & 0x80)) {
                uint8_t correction = *in++;
                for (i = 0; i < (length & 0x7F) + 2; i++) {
                    Check(size < len);
                    out += ar_conv_rune_to_utf8(((uint16_t)highbyte << 8) | (data[size] + (correction & 0xFF)), out, end_out - out);
                    size++;
                }
            }
            else {
                for (i = 0; i < (length & 0x7F) + 2; i++) {
                    Check(size < len);
                    out += ar_conv_rune_to_utf8(data[size], out, end_out - out);
                    size++;
                }
            }
            break;
        }
    }

    return str;

#undef Check
}