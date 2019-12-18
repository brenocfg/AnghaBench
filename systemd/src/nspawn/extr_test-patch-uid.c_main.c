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
typedef  int /*<<< orphan*/  uid_t ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  log_error (char*) ; 
 int /*<<< orphan*/  log_error_errno (int,char*,...) ; 
 int /*<<< orphan*/  log_info (char*,int /*<<< orphan*/ ) ; 
 int parse_gid (char*,int /*<<< orphan*/ *) ; 
 int parse_uid (char*,int /*<<< orphan*/ *) ; 
 int path_patch_uid (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yes_no (int) ; 

int main(int argc, char *argv[]) {
        uid_t shift, range;
        int r;

        test_setup_logging(LOG_DEBUG);

        if (argc != 4) {
                log_error("Expected PATH SHIFT RANGE parameters.");
                return EXIT_FAILURE;
        }

        r = parse_uid(argv[2], &shift);
        if (r < 0) {
                log_error_errno(r, "Failed to parse UID shift %s.", argv[2]);
                return EXIT_FAILURE;
        }

        r = parse_gid(argv[3], &range);
        if (r < 0) {
                log_error_errno(r, "Failed to parse UID range %s.", argv[3]);
                return EXIT_FAILURE;
        }

        r = path_patch_uid(argv[1], shift, range);
        if (r < 0) {
                log_error_errno(r, "Failed to patch directory tree: %m");
                return EXIT_FAILURE;
        }

        log_info("Changed: %s", yes_no(r));

        return EXIT_SUCCESS;
}