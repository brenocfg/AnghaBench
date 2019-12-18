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
typedef  int /*<<< orphan*/  ItemType ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_FILES ; 
 int /*<<< orphan*/  CREATE_BLOCK_DEVICE ; 
 int /*<<< orphan*/  CREATE_CHAR_DEVICE ; 
 int /*<<< orphan*/  CREATE_DIRECTORY ; 
 int /*<<< orphan*/  CREATE_FIFO ; 
 int /*<<< orphan*/  CREATE_FILE ; 
 int /*<<< orphan*/  CREATE_SUBVOLUME ; 
 int /*<<< orphan*/  CREATE_SUBVOLUME_INHERIT_QUOTA ; 
 int /*<<< orphan*/  CREATE_SUBVOLUME_NEW_QUOTA ; 
 int /*<<< orphan*/  CREATE_SYMLINK ; 
 int /*<<< orphan*/  EMPTY_DIRECTORY ; 
 int /*<<< orphan*/  IGNORE_DIRECTORY_PATH ; 
 int /*<<< orphan*/  IGNORE_PATH ; 
 int IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RECURSIVE_REMOVE_PATH ; 
 int /*<<< orphan*/  REMOVE_PATH ; 
 int /*<<< orphan*/  TRUNCATE_DIRECTORY ; 
 int /*<<< orphan*/  TRUNCATE_FILE ; 
 int /*<<< orphan*/  WRITE_FILE ; 

__attribute__((used)) static bool takes_ownership(ItemType t) {
        return IN_SET(t,
                      CREATE_FILE,
                      TRUNCATE_FILE,
                      CREATE_DIRECTORY,
                      EMPTY_DIRECTORY,
                      TRUNCATE_DIRECTORY,
                      CREATE_SUBVOLUME,
                      CREATE_SUBVOLUME_INHERIT_QUOTA,
                      CREATE_SUBVOLUME_NEW_QUOTA,
                      CREATE_FIFO,
                      CREATE_SYMLINK,
                      CREATE_CHAR_DEVICE,
                      CREATE_BLOCK_DEVICE,
                      COPY_FILES,
                      WRITE_FILE,
                      IGNORE_PATH,
                      IGNORE_DIRECTORY_PATH,
                      REMOVE_PATH,
                      RECURSIVE_REMOVE_PATH);
}