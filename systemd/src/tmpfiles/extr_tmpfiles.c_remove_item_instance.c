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
struct TYPE_4__ {int type; } ;
typedef  TYPE_1__ Item ;

/* Variables and functions */
 int ENOENT ; 
#define  RECURSIVE_REMOVE_PATH 129 
#define  REMOVE_PATH 128 
 int REMOVE_PHYSICAL ; 
 int REMOVE_ROOT ; 
 int REMOVE_SUBVOLUME ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int errno ; 
 int /*<<< orphan*/  log_debug (char*,char const*) ; 
 int log_error_errno (int,char*,char const*) ; 
 int /*<<< orphan*/  remove (char const*) ; 
 int rm_rf (char const*,int) ; 

__attribute__((used)) static int remove_item_instance(Item *i, const char *instance) {
        int r;

        assert(i);

        switch (i->type) {

        case REMOVE_PATH:
                if (remove(instance) < 0 && errno != ENOENT)
                        return log_error_errno(errno, "rm(%s): %m", instance);

                break;

        case RECURSIVE_REMOVE_PATH:
                /* FIXME: we probably should use dir_cleanup() here instead of rm_rf() so that 'x' is honoured. */
                log_debug("rm -rf \"%s\"", instance);
                r = rm_rf(instance, REMOVE_ROOT|REMOVE_SUBVOLUME|REMOVE_PHYSICAL);
                if (r < 0 && r != -ENOENT)
                        return log_error_errno(r, "rm_rf(%s): %m", instance);

                break;

        default:
                assert_not_reached("wut?");
        }

        return 0;
}