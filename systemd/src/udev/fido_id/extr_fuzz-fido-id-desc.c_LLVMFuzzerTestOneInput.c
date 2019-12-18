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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 size_t HID_MAX_DESCRIPTOR_SIZE ; 
 int /*<<< orphan*/  LOG_CRIT ; 
 int /*<<< orphan*/  getenv (char*) ; 
 int /*<<< orphan*/  is_fido_security_token_desc (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  log_set_max_level (int /*<<< orphan*/ ) ; 

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
        /* We don't want to fill the logs with messages about parse errors.
         * Disable most logging if not running standalone */
        if (!getenv("SYSTEMD_LOG_LEVEL"))
                log_set_max_level(LOG_CRIT);

        if (size > HID_MAX_DESCRIPTOR_SIZE)
                return 0;
        (void) is_fido_security_token_desc(data, size);

        return 0;
}