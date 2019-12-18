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
 int /*<<< orphan*/  strscpy (char*,size_t,char const*) ; 
 int strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_usb_mass_storage_ifsubtype(char *to, const char *from, size_t len) {
        int type_num = 0;
        char *eptr;
        const char *type = "generic";

        type_num = strtoul(from, &eptr, 0);
        if (eptr != from) {
                switch (type_num) {
                case 1: /* RBC devices */
                        type = "rbc";
                        break;
                case 2:
                        type = "atapi";
                        break;
                case 3:
                        type = "tape";
                        break;
                case 4: /* UFI */
                        type = "floppy";
                        break;
                case 6: /* Transparent SPC-2 devices */
                        type = "scsi";
                        break;
                default:
                        break;
                }
        }
        strscpy(to, len, type);
        return type_num;
}