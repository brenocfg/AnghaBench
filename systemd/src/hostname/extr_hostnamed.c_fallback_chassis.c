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
 scalar_t__ VIRTUALIZATION_IS_CONTAINER (int) ; 
 scalar_t__ VIRTUALIZATION_IS_VM (int) ; 
 int detect_virtualization () ; 
 int /*<<< orphan*/  free (char*) ; 
 int read_one_line_file (char*,char**) ; 
 int safe_atou (char*,unsigned int*) ; 

__attribute__((used)) static const char* fallback_chassis(void) {
        char *type;
        unsigned t;
        int v, r;

        v = detect_virtualization();
        if (VIRTUALIZATION_IS_VM(v))
                return "vm";
        if (VIRTUALIZATION_IS_CONTAINER(v))
                return "container";

        r = read_one_line_file("/sys/class/dmi/id/chassis_type", &type);
        if (r < 0)
                goto try_acpi;

        r = safe_atou(type, &t);
        free(type);
        if (r < 0)
                goto try_acpi;

        /* We only list the really obvious cases here. The DMI data is unreliable enough, so let's not do any
           additional guesswork on top of that.

           See the SMBIOS Specification 3.0 section 7.4.1 for details about the values listed here:

           https://www.dmtf.org/sites/default/files/standards/documents/DSP0134_3.0.0.pdf
         */

        switch (t) {

        case 0x3: /* Desktop */
        case 0x4: /* Low Profile Desktop */
        case 0x6: /* Mini Tower */
        case 0x7: /* Tower */
                return "desktop";

        case 0x8: /* Portable */
        case 0x9: /* Laptop */
        case 0xA: /* Notebook */
        case 0xE: /* Sub Notebook */
                return "laptop";

        case 0xB: /* Hand Held */
                return "handset";

        case 0x11: /* Main Server Chassis */
        case 0x1C: /* Blade */
        case 0x1D: /* Blade Enclosure */
                return "server";

        case 0x1E: /* Tablet */
                return "tablet";

        case 0x1F: /* Convertible */
        case 0x20: /* Detachable */
                return "convertible";
        }

try_acpi:
        r = read_one_line_file("/sys/firmware/acpi/pm_profile", &type);
        if (r < 0)
                return NULL;

        r = safe_atou(type, &t);
        free(type);
        if (r < 0)
                return NULL;

        /* We only list the really obvious cases here as the ACPI data is not really super reliable.
         *
         * See the ACPI 5.0 Spec Section 5.2.9.1 for details:
         *
         * http://www.acpi.info/DOWNLOADS/ACPIspec50.pdf
         */

        switch(t) {

        case 1: /* Desktop */
        case 3: /* Workstation */
        case 6: /* Appliance PC */
                return "desktop";

        case 2: /* Mobile */
                return "laptop";

        case 4: /* Enterprise Server */
        case 5: /* SOHO Server */
        case 7: /* Performance Server */
                return "server";

        case 8: /* Tablet */
                return "tablet";
        }

        return NULL;
}