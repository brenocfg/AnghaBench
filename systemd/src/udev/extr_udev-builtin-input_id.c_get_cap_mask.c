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
typedef  int /*<<< orphan*/  sd_device ;

/* Variables and functions */
 unsigned int BITS_PER_LONG ; 
 int /*<<< orphan*/  DISABLE_WARNING_FORMAT_NONLITERAL ; 
 int /*<<< orphan*/  REENABLE_WARNING ; 
 int /*<<< orphan*/  log_device_debug (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  memzero (unsigned long*,size_t) ; 
 scalar_t__ sd_device_get_sysattr_value (int /*<<< orphan*/ *,char const*,char const**) ; 
 char* strrchr (char*,char) ; 
 unsigned long strtoul (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xsprintf (char*,char*,...) ; 

__attribute__((used)) static void get_cap_mask(sd_device *pdev, const char* attr,
                         unsigned long *bitmask, size_t bitmask_size,
                         bool test) {
        const char *v;
        char text[4096];
        unsigned i;
        char* word;
        unsigned long val;

        if (sd_device_get_sysattr_value(pdev, attr, &v) < 0)
                v = "";

        xsprintf(text, "%s", v);
        log_device_debug(pdev, "%s raw kernel attribute: %s", attr, text);

        memzero(bitmask, bitmask_size);
        i = 0;
        while ((word = strrchr(text, ' ')) != NULL) {
                val = strtoul(word+1, NULL, 16);
                if (i < bitmask_size / sizeof(unsigned long))
                        bitmask[i] = val;
                else
                        log_device_debug(pdev, "Ignoring %s block %lX which is larger than maximum size", attr, val);
                *word = '\0';
                ++i;
        }
        val = strtoul (text, NULL, 16);
        if (i < bitmask_size / sizeof(unsigned long))
                bitmask[i] = val;
        else
                log_device_debug(pdev, "Ignoring %s block %lX which is larger than maximum size", attr, val);

        if (test) {
                /* printf pattern with the right unsigned long number of hex chars */
                xsprintf(text, "  bit %%4u: %%0%zulX\n",
                         2 * sizeof(unsigned long));
                log_device_debug(pdev, "%s decoded bit map:", attr);
                val = bitmask_size / sizeof (unsigned long);
                /* skip over leading zeros */
                while (bitmask[val-1] == 0 && val > 0)
                        --val;
                for (i = 0; i < val; ++i) {
                        DISABLE_WARNING_FORMAT_NONLITERAL;
                        log_device_debug(pdev, text, i * BITS_PER_LONG, bitmask[i]);
                        REENABLE_WARNING;
                }
        }
}