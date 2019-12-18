#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uid_t ;
typedef  int key_serial_t ;
typedef  scalar_t__ gid_t ;
struct TYPE_10__ {scalar_t__ keyring_mode; int /*<<< orphan*/  invocation_id; } ;
typedef  TYPE_1__ Unit ;
typedef  TYPE_1__ ExecParameters ;
typedef  TYPE_1__ ExecContext ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 scalar_t__ EDQUOT ; 
 scalar_t__ ENOSYS ; 
 int /*<<< orphan*/  EPERM ; 
 scalar_t__ EXEC_KEYRING_INHERIT ; 
 scalar_t__ EXEC_KEYRING_SHARED ; 
 scalar_t__ IN_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEYCTL_JOIN_SESSION_KEYRING ; 
 int /*<<< orphan*/  KEYCTL_LINK ; 
 int /*<<< orphan*/  KEYCTL_SETPERM ; 
 int KEY_POS_READ ; 
 int KEY_POS_SEARCH ; 
 int KEY_POS_VIEW ; 
 int KEY_SPEC_SESSION_KEYRING ; 
 int KEY_SPEC_USER_KEYRING ; 
 int KEY_USR_READ ; 
 int KEY_USR_SEARCH ; 
 int KEY_USR_VIEW ; 
 int add_key (char*,char*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 scalar_t__ errno ; 
 scalar_t__ getgid () ; 
 scalar_t__ getuid () ; 
 scalar_t__ gid_is_valid (scalar_t__) ; 
 scalar_t__ keyctl (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_unit_debug_errno (TYPE_1__ const*,scalar_t__,char*) ; 
 int log_unit_error_errno (TYPE_1__ const*,scalar_t__,char*) ; 
 int /*<<< orphan*/  sd_id128_is_null (int /*<<< orphan*/ ) ; 
 scalar_t__ setregid (scalar_t__,int) ; 
 scalar_t__ setreuid (scalar_t__,int) ; 
 scalar_t__ uid_is_valid (scalar_t__) ; 

__attribute__((used)) static int setup_keyring(
                const Unit *u,
                const ExecContext *context,
                const ExecParameters *p,
                uid_t uid, gid_t gid) {

        key_serial_t keyring;
        int r = 0;
        uid_t saved_uid;
        gid_t saved_gid;

        assert(u);
        assert(context);
        assert(p);

        /* Let's set up a new per-service "session" kernel keyring for each system service. This has the benefit that
         * each service runs with its own keyring shared among all processes of the service, but with no hook-up beyond
         * that scope, and in particular no link to the per-UID keyring. If we don't do this the keyring will be
         * automatically created on-demand and then linked to the per-UID keyring, by the kernel. The kernel's built-in
         * on-demand behaviour is very appropriate for login users, but probably not so much for system services, where
         * UIDs are not necessarily specific to a service but reused (at least in the case of UID 0). */

        if (context->keyring_mode == EXEC_KEYRING_INHERIT)
                return 0;

        /* Acquiring a reference to the user keyring is nasty. We briefly change identity in order to get things set up
         * properly by the kernel. If we don't do that then we can't create it atomically, and that sucks for parallel
         * execution. This mimics what pam_keyinit does, too. Setting up session keyring, to be owned by the right user
         * & group is just as nasty as acquiring a reference to the user keyring. */

        saved_uid = getuid();
        saved_gid = getgid();

        if (gid_is_valid(gid) && gid != saved_gid) {
                if (setregid(gid, -1) < 0)
                        return log_unit_error_errno(u, errno, "Failed to change GID for user keyring: %m");
        }

        if (uid_is_valid(uid) && uid != saved_uid) {
                if (setreuid(uid, -1) < 0) {
                        r = log_unit_error_errno(u, errno, "Failed to change UID for user keyring: %m");
                        goto out;
                }
        }

        keyring = keyctl(KEYCTL_JOIN_SESSION_KEYRING, 0, 0, 0, 0);
        if (keyring == -1) {
                if (errno == ENOSYS)
                        log_unit_debug_errno(u, errno, "Kernel keyring not supported, ignoring.");
                else if (IN_SET(errno, EACCES, EPERM))
                        log_unit_debug_errno(u, errno, "Kernel keyring access prohibited, ignoring.");
                else if (errno == EDQUOT)
                        log_unit_debug_errno(u, errno, "Out of kernel keyrings to allocate, ignoring.");
                else
                        r = log_unit_error_errno(u, errno, "Setting up kernel keyring failed: %m");

                goto out;
        }

        /* When requested link the user keyring into the session keyring. */
        if (context->keyring_mode == EXEC_KEYRING_SHARED) {

                if (keyctl(KEYCTL_LINK,
                           KEY_SPEC_USER_KEYRING,
                           KEY_SPEC_SESSION_KEYRING, 0, 0) < 0) {
                        r = log_unit_error_errno(u, errno, "Failed to link user keyring into session keyring: %m");
                        goto out;
                }
        }

        /* Restore uid/gid back */
        if (uid_is_valid(uid) && uid != saved_uid) {
                if (setreuid(saved_uid, -1) < 0) {
                        r = log_unit_error_errno(u, errno, "Failed to change UID back for user keyring: %m");
                        goto out;
                }
        }

        if (gid_is_valid(gid) && gid != saved_gid) {
                if (setregid(saved_gid, -1) < 0)
                        return log_unit_error_errno(u, errno, "Failed to change GID back for user keyring: %m");
        }

        /* Populate they keyring with the invocation ID by default, as original saved_uid. */
        if (!sd_id128_is_null(u->invocation_id)) {
                key_serial_t key;

                key = add_key("user", "invocation_id", &u->invocation_id, sizeof(u->invocation_id), KEY_SPEC_SESSION_KEYRING);
                if (key == -1)
                        log_unit_debug_errno(u, errno, "Failed to add invocation ID to keyring, ignoring: %m");
                else {
                        if (keyctl(KEYCTL_SETPERM, key,
                                   KEY_POS_VIEW|KEY_POS_READ|KEY_POS_SEARCH|
                                   KEY_USR_VIEW|KEY_USR_READ|KEY_USR_SEARCH, 0, 0) < 0)
                                r = log_unit_error_errno(u, errno, "Failed to restrict invocation ID permission: %m");
                }
        }

out:
        /* Revert back uid & gid for the the last time, and exit */
        /* no extra logging, as only the first already reported error matters */
        if (getuid() != saved_uid)
                (void) setreuid(saved_uid, -1);

        if (getgid() != saved_gid)
                (void) setregid(saved_gid, -1);

        return r;
}