#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int done; scalar_t__ allow_failure; int /*<<< orphan*/  path; } ;
typedef  int OperationMask ;
typedef  TYPE_1__ Item ;

/* Variables and functions */
 int CHASE_NO_AUTOFS ; 
 int CHASE_WARN ; 
 int EREMOTE ; 
 scalar_t__ FLAGS_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPERATION_CLEAN ; 
 int /*<<< orphan*/  OPERATION_CREATE ; 
 int /*<<< orphan*/  OPERATION_REMOVE ; 
 int /*<<< orphan*/  arg_root ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int chase_symlinks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int clean_item (TYPE_1__*) ; 
 int create_item (TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug_errno (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_notice_errno (int,char*,int /*<<< orphan*/ ) ; 
 int remove_item (TYPE_1__*) ; 

__attribute__((used)) static int process_item(Item *i, OperationMask operation) {
        OperationMask todo;
        int r, q, p;

        assert(i);

        todo = operation & ~i->done;
        if (todo == 0) /* Everything already done? */
                return 0;

        i->done |= operation;

        r = chase_symlinks(i->path, arg_root, CHASE_NO_AUTOFS|CHASE_WARN, NULL, NULL);
        if (r == -EREMOTE) {
                log_notice_errno(r, "Skipping %s", i->path);
                return 0;
        }
        if (r < 0)
                log_debug_errno(r, "Failed to determine whether '%s' is below autofs, ignoring: %m", i->path);

        r = FLAGS_SET(operation, OPERATION_CREATE) ? create_item(i) : 0;
        /* Failure can only be tolerated for create */
        if (i->allow_failure)
                r = 0;

        q = FLAGS_SET(operation, OPERATION_REMOVE) ? remove_item(i) : 0;
        p = FLAGS_SET(operation, OPERATION_CLEAN) ? clean_item(i) : 0;

        return r < 0 ? r :
                q < 0 ? q :
                p;
}