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
typedef  int char32_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  assert (char const*) ; 
 size_t utf8_encoded_expected_len (char const) ; 

int utf8_encoded_to_unichar(const char *str, char32_t *ret_unichar) {
        char32_t unichar;
        size_t len, i;

        assert(str);

        len = utf8_encoded_expected_len(str[0]);

        switch (len) {
        case 1:
                *ret_unichar = (char32_t)str[0];
                return 0;
        case 2:
                unichar = str[0] & 0x1f;
                break;
        case 3:
                unichar = (char32_t)str[0] & 0x0f;
                break;
        case 4:
                unichar = (char32_t)str[0] & 0x07;
                break;
        case 5:
                unichar = (char32_t)str[0] & 0x03;
                break;
        case 6:
                unichar = (char32_t)str[0] & 0x01;
                break;
        default:
                return -EINVAL;
        }

        for (i = 1; i < len; i++) {
                if (((char32_t)str[i] & 0xc0) != 0x80)
                        return -EINVAL;

                unichar <<= 6;
                unichar |= (char32_t)str[i] & 0x3f;
        }

        *ret_unichar = unichar;

        return 0;
}