#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
struct TYPE_4__ {int /*<<< orphan*/  path; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ JournalFile ;

/* Variables and functions */
 int add_acls_for_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ uid_for_system_journal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void server_add_acls(JournalFile *f, uid_t uid) {
#if HAVE_ACL
        int r;
#endif
        assert(f);

#if HAVE_ACL
        if (uid_for_system_journal(uid))
                return;

        r = add_acls_for_user(f->fd, uid);
        if (r < 0)
                log_warning_errno(r, "Failed to set ACL on %s, ignoring: %m", f->path);
#endif
}