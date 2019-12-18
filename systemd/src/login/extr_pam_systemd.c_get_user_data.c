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
typedef  char const passwd ;
typedef  char const* pam_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int PAM_AUTH_ERR ; 
 int PAM_SUCCESS ; 
 int PAM_USER_UNKNOWN ; 
 int /*<<< orphan*/  assert (char const**) ; 
 scalar_t__ isempty (char const*) ; 
 int pam_get_user (char const**,char const**,int /*<<< orphan*/ *) ; 
 char* pam_modutil_getpwnam (char const**,char const*) ; 
 int /*<<< orphan*/  pam_syslog (char const**,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int get_user_data(
                pam_handle_t *handle,
                const char **ret_username,
                struct passwd **ret_pw) {

        const char *username = NULL;
        struct passwd *pw = NULL;
        int r;

        assert(handle);
        assert(ret_username);
        assert(ret_pw);

        r = pam_get_user(handle, &username, NULL);
        if (r != PAM_SUCCESS) {
                pam_syslog(handle, LOG_ERR, "Failed to get user name.");
                return r;
        }

        if (isempty(username)) {
                pam_syslog(handle, LOG_ERR, "User name not valid.");
                return PAM_AUTH_ERR;
        }

        pw = pam_modutil_getpwnam(handle, username);
        if (!pw) {
                pam_syslog(handle, LOG_ERR, "Failed to get user data.");
                return PAM_USER_UNKNOWN;
        }

        *ret_pw = pw;
        *ret_username = username;

        return PAM_SUCCESS;
}