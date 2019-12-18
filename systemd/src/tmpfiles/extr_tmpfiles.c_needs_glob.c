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
 int /*<<< orphan*/  ADJUST_MODE ; 
 int /*<<< orphan*/  EMPTY_DIRECTORY ; 
 int /*<<< orphan*/  IGNORE_DIRECTORY_PATH ; 
 int /*<<< orphan*/  IGNORE_PATH ; 
 int IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RECURSIVE_RELABEL_PATH ; 
 int /*<<< orphan*/  RECURSIVE_REMOVE_PATH ; 
 int /*<<< orphan*/  RECURSIVE_SET_ACL ; 
 int /*<<< orphan*/  RECURSIVE_SET_ATTRIBUTE ; 
 int /*<<< orphan*/  RECURSIVE_SET_XATTR ; 
 int /*<<< orphan*/  RELABEL_PATH ; 
 int /*<<< orphan*/  REMOVE_PATH ; 
 int /*<<< orphan*/  SET_ACL ; 
 int /*<<< orphan*/  SET_ATTRIBUTE ; 
 int /*<<< orphan*/  SET_XATTR ; 
 int /*<<< orphan*/  WRITE_FILE ; 

__attribute__((used)) static bool needs_glob(ItemType t) {
        return IN_SET(t,
                      WRITE_FILE,
                      IGNORE_PATH,
                      IGNORE_DIRECTORY_PATH,
                      REMOVE_PATH,
                      RECURSIVE_REMOVE_PATH,
                      EMPTY_DIRECTORY,
                      ADJUST_MODE,
                      RELABEL_PATH,
                      RECURSIVE_RELABEL_PATH,
                      SET_XATTR,
                      RECURSIVE_SET_XATTR,
                      SET_ACL,
                      RECURSIVE_SET_ACL,
                      SET_ATTRIBUTE,
                      RECURSIVE_SET_ATTRIBUTE);
}