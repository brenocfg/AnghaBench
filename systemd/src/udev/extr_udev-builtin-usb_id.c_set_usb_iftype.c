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
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

__attribute__((used)) static void set_usb_iftype(char *to, int if_class_num, size_t len) {
        const char *type = "generic";

        switch (if_class_num) {
        case 1:
                type = "audio";
                break;
        case 2: /* CDC-Control */
                break;
        case 3:
                type = "hid";
                break;
        case 5: /* Physical */
                break;
        case 6:
                type = "media";
                break;
        case 7:
                type = "printer";
                break;
        case 8:
                type = "storage";
                break;
        case 9:
                type = "hub";
                break;
        case 0x0a: /* CDC-Data */
                break;
        case 0x0b: /* Chip/Smart Card */
                break;
        case 0x0d: /* Content Security */
                break;
        case 0x0e:
                type = "video";
                break;
        case 0xdc: /* Diagnostic Device */
                break;
        case 0xe0: /* Wireless Controller */
                break;
        case 0xfe: /* Application-specific */
                break;
        case 0xff: /* Vendor-specific */
                break;
        default:
                break;
        }
        strncpy(to, type, len);
        to[len-1] = '\0';
}