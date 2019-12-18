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
 int /*<<< orphan*/  ANY_LUKS ; 
 int CRYPT_MAX_SECTOR_SIZE ; 
 int /*<<< orphan*/  CRYPT_PLAIN ; 
 int CRYPT_SECTOR_SIZE ; 
 int /*<<< orphan*/  CRYPT_TCRYPT ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ STR_IN_SET (char const*,char*,char*,...) ; 
 int SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arg_cipher ; 
 int arg_discards ; 
 int /*<<< orphan*/  arg_hash ; 
 scalar_t__ arg_header ; 
 int arg_key_size ; 
 int /*<<< orphan*/  arg_key_slot ; 
 int /*<<< orphan*/  arg_keyfile_offset ; 
 int arg_keyfile_size ; 
 int /*<<< orphan*/  arg_offset ; 
 int arg_readonly ; 
 int arg_same_cpu_crypt ; 
 int arg_sector_size ; 
 int /*<<< orphan*/  arg_skip ; 
 int arg_submit_from_crypt_cpus ; 
 int arg_tcrypt_hidden ; 
 int /*<<< orphan*/  arg_tcrypt_keyfiles ; 
 int arg_tcrypt_system ; 
 int arg_tcrypt_veracrypt ; 
 int /*<<< orphan*/  arg_timeout ; 
 int arg_tries ; 
 int /*<<< orphan*/  arg_type ; 
 int arg_verify ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int free_and_strdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  log_error (char*,...) ; 
 int log_error_errno (int,char*,...) ; 
 int log_oom () ; 
 int /*<<< orphan*/  log_warning (char*,char const*) ; 
 int parse_sec_fix_0 (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ path_is_absolute (char const*) ; 
 int safe_atoi (char const*,int /*<<< orphan*/ *) ; 
 int safe_atou (char const*,int*) ; 
 int safe_atou64 (char const*,int /*<<< orphan*/ *) ; 
 char* startswith (char const*,char*) ; 
 scalar_t__ strdup (char const*) ; 
 scalar_t__ streq (char const*,char*) ; 
 scalar_t__ strv_extend (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int parse_one_option(const char *option) {
        const char *val;
        int r;

        assert(option);

        /* Handled outside of this tool */
        if (STR_IN_SET(option, "noauto", "auto", "nofail", "fail", "_netdev", "keyfile-timeout"))
                return 0;

        if (startswith(option, "keyfile-timeout="))
                return 0;

        if ((val = startswith(option, "cipher="))) {
                r = free_and_strdup(&arg_cipher, val);
                if (r < 0)
                        return log_oom();

        } else if ((val = startswith(option, "size="))) {

                r = safe_atou(val, &arg_key_size);
                if (r < 0) {
                        log_error_errno(r, "Failed to parse %s, ignoring: %m", option);
                        return 0;
                }

                if (arg_key_size % 8) {
                        log_error("size= not a multiple of 8, ignoring.");
                        return 0;
                }

                arg_key_size /= 8;

        } else if ((val = startswith(option, "sector-size="))) {

                r = safe_atou(val, &arg_sector_size);
                if (r < 0) {
                        log_error_errno(r, "Failed to parse %s, ignoring: %m", option);
                        return 0;
                }

                if (arg_sector_size % 2) {
                        log_error("sector-size= not a multiple of 2, ignoring.");
                        return 0;
                }

                if (arg_sector_size < CRYPT_SECTOR_SIZE || arg_sector_size > CRYPT_MAX_SECTOR_SIZE) {
                        log_error("sector-size= is outside of %u and %u, ignoring.", CRYPT_SECTOR_SIZE, CRYPT_MAX_SECTOR_SIZE);
                        return 0;
                }

        } else if ((val = startswith(option, "key-slot="))) {

                arg_type = ANY_LUKS;
                r = safe_atoi(val, &arg_key_slot);
                if (r < 0) {
                        log_error_errno(r, "Failed to parse %s, ignoring: %m", option);
                        return 0;
                }

        } else if ((val = startswith(option, "tcrypt-keyfile="))) {

                arg_type = CRYPT_TCRYPT;
                if (path_is_absolute(val)) {
                        if (strv_extend(&arg_tcrypt_keyfiles, val) < 0)
                                return log_oom();
                } else
                        log_error("Key file path \"%s\" is not absolute. Ignoring.", val);

        } else if ((val = startswith(option, "keyfile-size="))) {

                r = safe_atou(val, &arg_keyfile_size);
                if (r < 0) {
                        log_error_errno(r, "Failed to parse %s, ignoring: %m", option);
                        return 0;
                }

        } else if ((val = startswith(option, "keyfile-offset="))) {

                r = safe_atou64(val, &arg_keyfile_offset);
                if (r < 0) {
                        log_error_errno(r, "Failed to parse %s, ignoring: %m", option);
                        return 0;
                }

        } else if ((val = startswith(option, "hash="))) {
                r = free_and_strdup(&arg_hash, val);
                if (r < 0)
                        return log_oom();

        } else if ((val = startswith(option, "header="))) {
                arg_type = ANY_LUKS;

                if (!path_is_absolute(val))
                        return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                                               "Header path \"%s\" is not absolute, refusing.", val);

                if (arg_header)
                        return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                                               "Duplicate header= option, refusing.");

                arg_header = strdup(val);
                if (!arg_header)
                        return log_oom();

        } else if ((val = startswith(option, "tries="))) {

                r = safe_atou(val, &arg_tries);
                if (r < 0) {
                        log_error_errno(r, "Failed to parse %s, ignoring: %m", option);
                        return 0;
                }

        } else if (STR_IN_SET(option, "readonly", "read-only"))
                arg_readonly = true;
        else if (streq(option, "verify"))
                arg_verify = true;
        else if (STR_IN_SET(option, "allow-discards", "discard"))
                arg_discards = true;
        else if (streq(option, "same-cpu-crypt"))
                arg_same_cpu_crypt = true;
        else if (streq(option, "submit-from-crypt-cpus"))
                arg_submit_from_crypt_cpus = true;
        else if (streq(option, "luks"))
                arg_type = ANY_LUKS;
        else if (streq(option, "tcrypt"))
                arg_type = CRYPT_TCRYPT;
        else if (streq(option, "tcrypt-hidden")) {
                arg_type = CRYPT_TCRYPT;
                arg_tcrypt_hidden = true;
        } else if (streq(option, "tcrypt-system")) {
                arg_type = CRYPT_TCRYPT;
                arg_tcrypt_system = true;
        } else if (streq(option, "tcrypt-veracrypt")) {
                arg_type = CRYPT_TCRYPT;
                arg_tcrypt_veracrypt = true;
        } else if (STR_IN_SET(option, "plain", "swap", "tmp"))
                arg_type = CRYPT_PLAIN;
        else if ((val = startswith(option, "timeout="))) {

                r = parse_sec_fix_0(val, &arg_timeout);
                if (r < 0) {
                        log_error_errno(r, "Failed to parse %s, ignoring: %m", option);
                        return 0;
                }

        } else if ((val = startswith(option, "offset="))) {

                r = safe_atou64(val, &arg_offset);
                if (r < 0)
                        return log_error_errno(r, "Failed to parse %s: %m", option);

        } else if ((val = startswith(option, "skip="))) {

                r = safe_atou64(val, &arg_skip);
                if (r < 0)
                        return log_error_errno(r, "Failed to parse %s: %m", option);

        } else if (!streq(option, "none"))
                log_warning("Encountered unknown /etc/crypttab option '%s', ignoring.", option);

        return 0;
}