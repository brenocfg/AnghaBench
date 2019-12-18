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
struct write_queue_item {int /*<<< orphan*/  file; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int WRITE_STRING_FILE_ATOMIC ; 
 int WRITE_STRING_FILE_CREATE ; 
 int WRITE_STRING_FILE_MKDIR_0755 ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int log_error_errno (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  one_zero (int /*<<< orphan*/ ) ; 
 int write_string_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int save_state_write_one(struct write_queue_item *item) {
        int r;

        r = write_string_file(item->file, one_zero(item->state), WRITE_STRING_FILE_CREATE|WRITE_STRING_FILE_ATOMIC|WRITE_STRING_FILE_MKDIR_0755);
        if (r < 0)
                return log_error_errno(r, "Failed to write state file %s: %m", item->file);

        log_debug("Saved state '%s' to %s.", one_zero(item->state), item->file);
        return 0;
}