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
struct TYPE_7__ {int type; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ Item ;

/* Variables and functions */
#define  COPY_FILES 136 
#define  CREATE_DIRECTORY 135 
#define  CREATE_SUBVOLUME 134 
#define  CREATE_SUBVOLUME_INHERIT_QUOTA 133 
#define  CREATE_SUBVOLUME_NEW_QUOTA 132 
#define  EMPTY_DIRECTORY 131 
#define  IGNORE_DIRECTORY_PATH 130 
#define  IGNORE_PATH 129 
#define  TRUNCATE_DIRECTORY 128 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  clean_item_instance (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int glob_item (TYPE_1__*,int /*<<< orphan*/  (*) (TYPE_1__*,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  log_debug (char*,char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clean_item(Item *i) {
        assert(i);

        log_debug("Running clean action for entry %c %s", (char) i->type, i->path);

        switch (i->type) {
        case CREATE_DIRECTORY:
        case CREATE_SUBVOLUME:
        case CREATE_SUBVOLUME_INHERIT_QUOTA:
        case CREATE_SUBVOLUME_NEW_QUOTA:
        case TRUNCATE_DIRECTORY:
        case IGNORE_PATH:
        case COPY_FILES:
                clean_item_instance(i, i->path);
                return 0;
        case EMPTY_DIRECTORY:
        case IGNORE_DIRECTORY_PATH:
                return glob_item(i, clean_item_instance);
        default:
                return 0;
        }
}