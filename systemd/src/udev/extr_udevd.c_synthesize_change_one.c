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
 int /*<<< orphan*/  WRITE_STRING_FILE_DISABLE_BUFFER ; 
 int /*<<< orphan*/  log_device_debug (int /*<<< orphan*/ *,char*,char const*) ; 
 int log_device_debug_errno (int /*<<< orphan*/ *,int,char*,char const*) ; 
 char* strjoina (char const*,char*) ; 
 int write_string_file (char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int synthesize_change_one(sd_device *dev, const char *syspath) {
        const char *filename;
        int r;

        filename = strjoina(syspath, "/uevent");
        log_device_debug(dev, "device is closed, synthesising 'change' on %s", syspath);
        r = write_string_file(filename, "change", WRITE_STRING_FILE_DISABLE_BUFFER);
        if (r < 0)
                return log_device_debug_errno(dev, r, "Failed to write 'change' to %s: %m", filename);
        return 0;
}