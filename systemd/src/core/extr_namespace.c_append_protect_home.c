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
typedef  int ProtectHome ;
typedef  int /*<<< orphan*/  MountEntry ;

/* Variables and functions */
 int /*<<< orphan*/  ELEMENTSOF (int /*<<< orphan*/ ) ; 
#define  PROTECT_HOME_NO 131 
#define  PROTECT_HOME_READ_ONLY 130 
#define  PROTECT_HOME_TMPFS 129 
#define  PROTECT_HOME_YES 128 
 int append_static_mounts (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int /*<<< orphan*/  protect_home_read_only_table ; 
 int /*<<< orphan*/  protect_home_tmpfs_table ; 
 int /*<<< orphan*/  protect_home_yes_table ; 

__attribute__((used)) static int append_protect_home(MountEntry **p, ProtectHome protect_home, bool ignore_protect) {
        assert(p);

        switch (protect_home) {

        case PROTECT_HOME_NO:
                return 0;

        case PROTECT_HOME_READ_ONLY:
                return append_static_mounts(p, protect_home_read_only_table, ELEMENTSOF(protect_home_read_only_table), ignore_protect);

        case PROTECT_HOME_TMPFS:
                return append_static_mounts(p, protect_home_tmpfs_table, ELEMENTSOF(protect_home_tmpfs_table), ignore_protect);

        case PROTECT_HOME_YES:
                return append_static_mounts(p, protect_home_yes_table, ELEMENTSOF(protect_home_yes_table), ignore_protect);

        default:
                assert_not_reached("Unexpected ProtectHome= value");
        }
}