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
typedef  char const pam_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  isempty (char const*) ; 
 char* pam_getenv (char const*,char const*) ; 
 char* secure_getenv (char const*) ; 

__attribute__((used)) static const char* getenv_harder(pam_handle_t *handle, const char *key, const char *fallback) {
        const char *v;

        assert(handle);
        assert(key);

        /* Looks for an environment variable, preferably in the environment block associated with the
         * specified PAM handle, falling back to the process' block instead. Why check both? Because we want
         * to permit configuration of session properties from unit files that invoke PAM services, so that
         * PAM services don't have to be reworked to set systemd-specific properties, but these properties
         * can still be set from the unit file Environment= block. */

        v = pam_getenv(handle, key);
        if (!isempty(v))
                return v;

        /* We use secure_getenv() here, since we might get loaded into su/sudo, which are SUID. Ideally
         * they'd clean up the environment before invoking foreign code (such as PAM modules), but alas they
         * currently don't (to be precise, they clean up the environment they pass to their children, but
         * not their own environ[]). */
        v = secure_getenv(key);
        if (!isempty(v))
                return v;

        return fallback;
}