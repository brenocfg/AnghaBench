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
 int /*<<< orphan*/  COPY_REFLINK ; 
 int ENOENT ; 
 int /*<<< orphan*/  F_OK ; 
 scalar_t__ arg_copy_locale ; 
 int /*<<< orphan*/  arg_locale ; 
 int /*<<< orphan*/  arg_locale_messages ; 
 scalar_t__ arg_root ; 
 int copy_file (char*,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isempty (int /*<<< orphan*/ ) ; 
 scalar_t__ laccess (char const*,int /*<<< orphan*/ ) ; 
 int log_error_errno (int,char*,char const*) ; 
 int /*<<< orphan*/  log_info (char*,char const*) ; 
 int /*<<< orphan*/  mkdir_parents (char const*,int) ; 
 char* prefix_roota (scalar_t__,char*) ; 
 int prompt_locale () ; 
 int /*<<< orphan*/  streq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strjoina (char*,int /*<<< orphan*/ ) ; 
 int write_env_file (char const*,char**) ; 

__attribute__((used)) static int process_locale(void) {
        const char *etc_localeconf;
        char* locales[3];
        unsigned i = 0;
        int r;

        etc_localeconf = prefix_roota(arg_root, "/etc/locale.conf");
        if (laccess(etc_localeconf, F_OK) >= 0)
                return 0;

        if (arg_copy_locale && arg_root) {

                (void) mkdir_parents(etc_localeconf, 0755);
                r = copy_file("/etc/locale.conf", etc_localeconf, 0, 0644, 0, 0, COPY_REFLINK);
                if (r != -ENOENT) {
                        if (r < 0)
                                return log_error_errno(r, "Failed to copy %s: %m", etc_localeconf);

                        log_info("%s copied.", etc_localeconf);
                        return 0;
                }
        }

        r = prompt_locale();
        if (r < 0)
                return r;

        if (!isempty(arg_locale))
                locales[i++] = strjoina("LANG=", arg_locale);
        if (!isempty(arg_locale_messages) && !streq(arg_locale_messages, arg_locale))
                locales[i++] = strjoina("LC_MESSAGES=", arg_locale_messages);

        if (i == 0)
                return 0;

        locales[i] = NULL;

        (void) mkdir_parents(etc_localeconf, 0755);
        r = write_env_file(etc_localeconf, locales);
        if (r < 0)
                return log_error_errno(r, "Failed to write %s: %m", etc_localeconf);

        log_info("%s written.", etc_localeconf);
        return 0;
}