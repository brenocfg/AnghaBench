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
typedef  int /*<<< orphan*/  ConditionType ;

/* Variables and functions */
 int /*<<< orphan*/  CONDITION_DIRECTORY_NOT_EMPTY ; 
 int /*<<< orphan*/  CONDITION_FILE_IS_EXECUTABLE ; 
 int /*<<< orphan*/  CONDITION_FILE_NOT_EMPTY ; 
 int /*<<< orphan*/  CONDITION_NEEDS_UPDATE ; 
 int /*<<< orphan*/  CONDITION_PATH_EXISTS ; 
 int /*<<< orphan*/  CONDITION_PATH_EXISTS_GLOB ; 
 int /*<<< orphan*/  CONDITION_PATH_IS_DIRECTORY ; 
 int /*<<< orphan*/  CONDITION_PATH_IS_MOUNT_POINT ; 
 int /*<<< orphan*/  CONDITION_PATH_IS_READ_WRITE ; 
 int /*<<< orphan*/  CONDITION_PATH_IS_SYMBOLIC_LINK ; 
 int IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool condition_takes_path(ConditionType t) {
        return IN_SET(t,
                      CONDITION_PATH_EXISTS,
                      CONDITION_PATH_EXISTS_GLOB,
                      CONDITION_PATH_IS_DIRECTORY,
                      CONDITION_PATH_IS_SYMBOLIC_LINK,
                      CONDITION_PATH_IS_MOUNT_POINT,
                      CONDITION_PATH_IS_READ_WRITE,
                      CONDITION_DIRECTORY_NOT_EMPTY,
                      CONDITION_FILE_NOT_EMPTY,
                      CONDITION_FILE_IS_EXECUTABLE,
                      CONDITION_NEEDS_UPDATE);
}