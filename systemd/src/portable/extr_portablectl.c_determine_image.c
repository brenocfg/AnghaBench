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
 scalar_t__ BUS_TRANSPORT_LOCAL ; 
 int CHASE_NONEXISTENT ; 
 int CHASE_TRAIL_SLASH ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  F_OK ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arg_quiet ; 
 scalar_t__ arg_transport ; 
 int chase_symlinks (char const*,int /*<<< orphan*/ *,int,char**,int /*<<< orphan*/ *) ; 
 scalar_t__ image_name_is_valid (char const*) ; 
 scalar_t__ laccess (char const*,int /*<<< orphan*/ ) ; 
 int log_error_errno (int,char*,...) ; 
 int log_oom () ; 
 int /*<<< orphan*/  log_warning (char*,char const*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int determine_image(const char *image, bool permit_non_existing, char **ret) {
        int r;

        /* If the specified name is a valid image name, we pass it as-is to portabled, which will search for it in the
         * usual search directories. Otherwise we presume it's a path, and will normalize it on the client's side
         * (among other things, to make the path independent of the client's working directory) before passing it
         * over. */

        if (image_name_is_valid(image)) {
                char *c;

                if (!arg_quiet && laccess(image, F_OK) >= 0)
                        log_warning("Ambiguous invocation: current working directory contains file matching non-path argument '%s', ignoring. "
                                    "Prefix argument with './' to force reference to file in current working directory.", image);

                c = strdup(image);
                if (!c)
                        return log_oom();

                *ret = c;
                return 0;
        }

        if (arg_transport != BUS_TRANSPORT_LOCAL)
                return log_error_errno(SYNTHETIC_ERRNO(EOPNOTSUPP),
                                       "Operations on images by path not supported when connecting to remote systems.");

        r = chase_symlinks(image, NULL, CHASE_TRAIL_SLASH | (permit_non_existing ? CHASE_NONEXISTENT : 0), ret, NULL);
        if (r < 0)
                return log_error_errno(r, "Cannot normalize specified image path '%s': %m", image);

        return 0;
}